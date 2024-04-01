#include <WiFi.h>
#include "Led.h"

class ActuatorClient {
private:
    WiFiClient client;
    Led* redLed;
    Led* yellowLed;
    Led* whiteLed;
    Led* blueLed;
public:
    ActuatorClient();
    ~ActuatorClient();
    void connectWithServer(const char* serverAddress, const int serverPort);
    const char* getPointerToConstantCharacterArray(String& string);
    void sendGetToServer();
    void terminateTheConnection();
    unsigned long getTimeElapsedSinceESPStarted();
    void waitMilliseconds(int milliseconds);
    int thereIsDataToBeReadFromTheServer();
    void waitForResponseFromTheServer(int milliseconds);
    String getGetRequestFromServer();
    void getLedsStatusBasedOnTheGetRequest(String getRequestFromServer);
    void turnLedsOnAndOffBasedOnGetRequest(String getRequestFromServer);
    void doSomethingBasedOnGetRequest();
};
