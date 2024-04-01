#include "ClientAdministrator.h"
#include <thread>
#include "ServerOptions.h"

constexpr int PORT = 7001;

class ServerAdministrator {
private:
    int serverListeningSocket;
    struct sockaddr_in serverListeningAddress;
public:
    ServerAdministrator();
    ~ServerAdministrator();
    void getAndSetListeningSocketFromServer();
    int* getPointerFromInteger(int opcionesAdicionales);
    int getBytesSizeOfAnInteger(int integer);
    void makeAdditionalConfigurationsToTheServerListeningSocket();
    void makeAdditionalConfigurationsToTheServerListeningAddress();
    struct sockaddr* castSockaddrInToSockaddrPointer(struct sockaddr_in* sockaddrIn);
    int getBytesSizeOfAnSockaddrIn(struct sockaddr_in sockaddrIn);
    void associateTheListeningSocketWithTheListeningIPAddress();
    void prepareToAcceptConnectionsOnTheSocket();
    socklen_t* castIntToSocklenTPointer(int* intValue);
    void createSocketForNewClient(int &socketForNewClient);
    void spawnClientHandlerThread(ClientAdministrator* clientAdministrator, LedController* ledController, MessageHandler* messageHandler,Temperature* temperature);
    void setServerListeningSocketAndConfigureIt();
    void configureTheServer();
    void listenToAndServeClients(LedController* ledController, MessageHandler* messageHandler,Temperature* temperature);
    void runTheServer();
    void startServer();
};