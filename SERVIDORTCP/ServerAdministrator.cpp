#include "ServerAdministrator.h"

ServerAdministrator::ServerAdministrator()
{
    this->sizeOfServerListeninsAddress = sizeof(this->serverListeningAddress);
    additionalOptions = 1;
    this->temperature = 0.0;
    std::memset(buffer, 0, BUFFER_SIZE);
    std::memset(nameMethod, 0, sizeof(nameMethod));
    redLed = false;
    yellowLed = false;
    whiteLed = false;
    blueLed = false;
}

ServerAdministrator::~ServerAdministrator() {
}

int ServerAdministrator::getListeningSocketFromServer()
{
    return socket(AF_INET, SOCK_STREAM, 0);
}

int* ServerAdministrator::getPointerFromInteger(int additionalOptions)
{
    int* pointerToInt = new int(additionalOptions);
    return pointerToInt;
}

int ServerAdministrator::getBytesSizeOfAnInteger(int integer)
{
    return sizeof(integer);
}

int ServerAdministrator::makeAdditionalConfigurationsToTheServerListeningSocket()
{
    return setsockopt(serverListeningSocket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, getPointerFromInteger(additionalOptions), getBytesSizeOfAnInteger(additionalOptions));
}

void ServerAdministrator::makeAdditionalConfigurationsToTheServerListeningAddress()
{
    serverListeningAddress.sin_family = AF_INET;
    serverListeningAddress.sin_addr.s_addr = INADDR_ANY;
    serverListeningAddress.sin_port = htons(PORT);
}

struct sockaddr* ServerAdministrator::castSockaddrInToSockaddrPointer(struct sockaddr_in* sockaddrIn)
{
    return reinterpret_cast<struct sockaddr*>(sockaddrIn);
}

int ServerAdministrator::getBytesSizeOfAnSockaddrIn(struct sockaddr_in sockaddrIn)
{
    return sizeof(sockaddrIn);
}

int ServerAdministrator::associateTheListeningSocketWithTheListeningIPAddress()
{
    return bind(serverListeningSocket, castSockaddrInToSockaddrPointer(&serverListeningAddress), getBytesSizeOfAnSockaddrIn(serverListeningAddress));
}

int ServerAdministrator::prepareToAcceptConnectionsOnTheSocket()
{
    return listen(serverListeningSocket, 3);
}

socklen_t* ServerAdministrator::castIntToSocklenTPointer(int* intValue)
{
    return reinterpret_cast<socklen_t*>(intValue);
}

int ServerAdministrator::createSocketForNewClient()
{
    return accept(serverListeningSocket, castSockaddrInToSockaddrPointer(&serverListeningAddress), castIntToSocklenTPointer(&sizeOfServerListeninsAddress));
}

void ServerAdministrator::spawnClientHandlerThread(ClientAdministrator* clientAdministrator, char* buffer, char* name_method, double* temperature, bool* redLed, bool* yellowLed, bool* whiteLed, bool* blueLed) {
    std::thread([clientAdministrator, buffer, name_method, temperature, redLed, yellowLed, whiteLed, blueLed]() {
        clientAdministrator->putSetOrSendGet(buffer, name_method, temperature, redLed, yellowLed, whiteLed, blueLed);
        delete clientAdministrator;
    }).detach();
}


void ServerAdministrator::startServer()
{
    if ((serverListeningSocket = getListeningSocketFromServer()) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (makeAdditionalConfigurationsToTheServerListeningSocket())
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    makeAdditionalConfigurationsToTheServerListeningAddress();

    if (associateTheListeningSocketWithTheListeningIPAddress() < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (prepareToAcceptConnectionsOnTheSocket() < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    std::cout << "Server listening on port " << PORT << std::endl;

    while (true)
    {
        if ((socketForNewClient = createSocketForNewClient()) < 0)
        {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        ClientAdministrator* clientAdministrator = new ClientAdministrator(socketForNewClient);
        spawnClientHandlerThread(clientAdministrator, buffer, nameMethod, &temperature, &redLed, &yellowLed, &whiteLed, &blueLed);
    }
}
