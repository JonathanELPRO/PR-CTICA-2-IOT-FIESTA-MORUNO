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
    bool connectWithServer(const char* serverAddress, const int serverPort);
    const char* getPointerToConstantCharacterArray(String& string);
    void sendGetToServer(String get_);
    void terminateTheConnection();
    unsigned long getTimeElapsedSinceESPStarted();
    void waitMilliseconds(int milliseconds);
    int thereIsDataToBeReadFromTheServer();
    void waitForResponseFromTheServer(int milliseconds);
    String getGetRequestFromServer();
    int getSubstringPositionInString(String string, String subString);
    char getCharacterOfAPositionOfAString(String string, int position_);
    int castCharToInt(char char_);
    void turnLedsOnAndOffBasedOnGetRequest(String getRequestFromServer);
};
