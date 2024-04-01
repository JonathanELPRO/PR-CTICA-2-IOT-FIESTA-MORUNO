#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include "LedController.h"
#include "MessageHandler.h"
#include "Temperature.h"

class ClientAdministrator {
private:
    int clientSocket;

public:
    ClientAdministrator(int clientSocket);
    ~ClientAdministrator();
    void updateLedsStatusFromTemperature(LedController* ledController, Temperature* temperature);
    int getNumberOfBytesOfMessageReceivedByTheClient(char* buffer);
    char* getPointerToCharacterFromString(char* string, char character);
    size_t getTheNumberOfCharactersBetweenTwoCharacterPointers(char* pointerChar1, char* pointerChar2);
    void copySubstringInOtherString(char* string, char* string2, size_t numberOfCharactersToCopy);
    void copyStringInOtherString(char* copiedString, char* stringToCopy);
    void identifyTheTypeOfMethod(char* buffer, char* nameMethod);
    bool stringsEquals(char* string1, const char* string2);
    void extractTemperatureFromBufferInVariable(char* buffer, double* temperature);
    char* getTheGetRequestMessage(LedController* ledController);
    int getTheSizeOfString(char* messageGet);
    void sendGetMessageToClient(char* messageGet);
    double* getPointerFromDouble(double& Double);
    void performTheSetProtocol(LedController* ledController, MessageHandler* messageHandler, Temperature* temperature);
    void performTheGetProtocol(LedController* ledController);
    void clearString(char* string, int sizeString);
    void endConnectionWithClient();
    void identifyAndProcessMethod(LedController* ledController, MessageHandler* messageHandler, Temperature* temperature);
    void processReceivedMessage(LedController* ledController, MessageHandler* messageHandler, Temperature* temperature);
    void putSetOrSendGet(LedController* ledController, MessageHandler* messageHandler, Temperature* temperature);
};
