#include "ClientAdministrator.h"
#include <thread>

constexpr int PORT = 7001;

class ServerAdministrator {
private:
    int serverListeningSocket;
    int socketForNewClient;
    struct sockaddr_in serverListeningAddress;
    int sizeOfServerListeninsAddress;
    int additionalOptions;
    bool redLed;
    bool yellowLed;
    bool whiteLed;
    bool blueLed;
    double temperature;
    char buffer[BUFFER_SIZE];
    char nameMethod[10];
public:
    ServerAdministrator();
    ~ServerAdministrator();
    int getListeningSocketFromServer();
    int* getPointerFromInteger(int opcionesAdicionales);
    int getBytesSizeOfAnInteger(int integer);
    int makeAdditionalConfigurationsToTheServerListeningSocket();
    void makeAdditionalConfigurationsToTheServerListeningAddress();
    struct sockaddr* castSockaddrInToSockaddrPointer(struct sockaddr_in* sockaddrIn);
    int getBytesSizeOfAnSockaddrIn(struct sockaddr_in sockaddrIn);
    int associateTheListeningSocketWithTheListeningIPAddress();
    int prepareToAcceptConnectionsOnTheSocket();
    socklen_t* castIntToSocklenTPointer(int* intValue);
    int createSocketForNewClient();
    void spawnClientHandlerThread(ClientAdministrator* clientAdministrator, char* buffer, char* nameMethod, double* temperature, bool* redLed, bool* yellowLed, bool* whiteLed, bool* blueLed);
    void startServer();
};
