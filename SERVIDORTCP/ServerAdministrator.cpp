#include "ServerAdministrator.h"

ServerAdministrator::ServerAdministrator() {
}

ServerAdministrator::~ServerAdministrator() {
}

void ServerAdministrator::getAndSetListeningSocketFromServer() {
    ServerOptions* serverOptions = new ServerOptions(0);
    if ((serverListeningSocket = socket(AF_INET, SOCK_STREAM, serverOptions->getAdditionalOptions())) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    delete serverOptions;
}

int* ServerAdministrator::getPointerFromInteger(int additionalOptions) {
    int* pointerToInt = new int(additionalOptions);
    return pointerToInt;
}

int ServerAdministrator::getBytesSizeOfAnInteger(int integer) {
    return sizeof(integer);
}

void ServerAdministrator::makeAdditionalConfigurationsToTheServerListeningSocket() {
    ServerOptions* serverOptions = new ServerOptions(1);
    if (setsockopt(serverListeningSocket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, getPointerFromInteger(serverOptions->getAdditionalOptions()), getBytesSizeOfAnInteger(serverOptions->getAdditionalOptions()))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    delete serverOptions;
}

void ServerAdministrator::makeAdditionalConfigurationsToTheServerListeningAddress() {
    serverListeningAddress.sin_family = AF_INET;
    serverListeningAddress.sin_addr.s_addr = INADDR_ANY;
    serverListeningAddress.sin_port = htons(PORT);
}

struct sockaddr* ServerAdministrator::castSockaddrInToSockaddrPointer(struct sockaddr_in* sockaddrIn) {
    return reinterpret_cast<struct sockaddr*>(sockaddrIn);
}

int ServerAdministrator::getBytesSizeOfAnSockaddrIn(struct sockaddr_in sockaddrIn) {
    return sizeof(sockaddrIn);
}

void ServerAdministrator::associateTheListeningSocketWithTheListeningIPAddress() {
    if (bind(serverListeningSocket, castSockaddrInToSockaddrPointer(&serverListeningAddress), getBytesSizeOfAnSockaddrIn(serverListeningAddress)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
}

void ServerAdministrator::prepareToAcceptConnectionsOnTheSocket() {
    if (listen(serverListeningSocket, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
}

socklen_t* ServerAdministrator::castIntToSocklenTPointer(int* intValue) {
    return reinterpret_cast<socklen_t*>(intValue);
}

void ServerAdministrator::createSocketForNewClient(int &socketForNewClient) {
    int sizeOfServerListeningAddress = sizeof(this->serverListeningAddress);
    if ((socketForNewClient = accept(serverListeningSocket, castSockaddrInToSockaddrPointer(&serverListeningAddress), castIntToSocklenTPointer(&sizeOfServerListeningAddress))) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
}

void ServerAdministrator::spawnClientHandlerThread(ClientAdministrator* clientAdministrator, LedController* ledController, MessageHandler* messageHandler, Temperature* temperature) {
    std::thread([clientAdministrator, ledController, messageHandler, temperature]() {
        clientAdministrator->putSetOrSendGet(ledController, messageHandler, temperature);
        delete clientAdministrator;
    }).detach();
}

void ServerAdministrator::setServerListeningSocketAndConfigureIt() {
    getAndSetListeningSocketFromServer();
    makeAdditionalConfigurationsToTheServerListeningSocket();
}

void ServerAdministrator::configureTheServer() {
    setServerListeningSocketAndConfigureIt();
    makeAdditionalConfigurationsToTheServerListeningAddress();
    associateTheListeningSocketWithTheListeningIPAddress();
    prepareToAcceptConnectionsOnTheSocket();
}

void ServerAdministrator::listenToAndServeClients(LedController* ledController, MessageHandler* messageHandler, Temperature* temperature) {
    int socketForNewClient;
    bool running = true
    while (running) {
        createSocketForNewClient(socketForNewClient);
        ClientAdministrator* clientAdministrator = new ClientAdministrator(socketForNewClient);
        spawnClientHandlerThread(clientAdministrator, ledController, messageHandler, temperature);
    }
}

void ServerAdministrator::runTheServer() {
    LedController* ledController = new LedController();
    MessageHandler* messageHandler = new MessageHandler();
    Temperature* temperature = new Temperature(0.0);
    std::cout << "Server listening on port " << PORT << std::endl;
    listenToAndServeClients(ledController, messageHandler, temperature);
}

void ServerAdministrator::startServer() {
    configureTheServer();
    runTheServer();
}
