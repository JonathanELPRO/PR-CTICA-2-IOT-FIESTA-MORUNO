#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

constexpr int BUFFER_SIZE = 1024;

class ClientAdministrator {
private:
    int clientSocket;

public:
    ClientAdministrator(int clientSocket);
    ~ClientAdministrator();
    void updateLedsStatusFromTemperature(bool *redLed, bool *yellowLed, bool *whiteLed, bool *blueLed, double *temperature);
    int getNumberOfBytesOfMessageReceivedByTheClient(char *buffer);
    char* getPointerToCharacterFromString(char* string, char character);
    size_t getTheNumberOfCharactersBetweenTwoCharacterPointers(char* pointerChar1, char* pointerChar2);
    void copySubstringInOtherString(char* string, char* string2, size_t numberOfCharactersToCopy);
    void copyStringInOtherString(char* copiedString, char* stringToCopy);
    void identifyTheTypeOfMethod(char* buffer, char* nameMethod);
    bool stringsEquals(char* string1,const char* string2);
    void extractTemperatureFromBufferInVariable(char* buffer, double *temperature);
    char* getTheGetRequestMessage(bool* redLed, bool* yellowLed, bool* whiteLed, bool* blueLed);
    int getTheSizeOfString(char* messageGet);
    void sendGetMessageToClient(char* messageGet);
    void performTheSetProtocol(char* buffer, double* temperature, bool* redLed, bool* yellowLed, bool* whiteLed, bool* blueLed);
    void performTheGetProtocol(bool* redLed, bool* yellowLed, bool* whiteLed, bool* blueLed);
    void clearString(char* string, int sizeString);
    void endConnectionWithClient();
    void putSetOrSendGet(char* buffer, char* nameMethod, double* temperature, bool* redLed, bool* yellowLed, bool* whiteLed, bool* blueLed);
};