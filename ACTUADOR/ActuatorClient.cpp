#include "ActuatorClient.h"

ActuatorClient::ActuatorClient() {
    redLed = new Led(13);
    yellowLed = new Led(27);
    whiteLed = new Led(26);
    blueLed = new Led(25);
}

ActuatorClient::~ActuatorClient() {
}

bool ActuatorClient::connectWithServer(const char* serverAddress, const int serverPort) {
    return client.connect(serverAddress, serverPort);
}

const char* ActuatorClient::getPointerToConstantCharacterArray(String& string) {
    return string.c_str();
}

void ActuatorClient::sendGetToServer(String get_) {
    client.print(getPointerToConstantCharacterArray(get_));
}

void ActuatorClient::terminateTheConnection() {
    client.stop();
}

unsigned long ActuatorClient::getTimeElapsedSinceESPStarted() {
    return millis();
}

void ActuatorClient::waitMilliseconds(int milliseconds) {
    unsigned long previousTimeElapsedSinceESPStarted = getTimeElapsedSinceESPStarted();
    while (getTimeElapsedSinceESPStarted() - previousTimeElapsedSinceESPStarted < milliseconds);
}

int ActuatorClient::thereIsDataToBeReadFromTheServer() {
    return client.available();
}

void ActuatorClient::waitForResponseFromTheServer(int milliseconds) {
    unsigned long previousTimeElapsedSinceESPStarted = getTimeElapsedSinceESPStarted();
    while (!thereIsDataToBeReadFromTheServer() && getTimeElapsedSinceESPStarted() - previousTimeElapsedSinceESPStarted < milliseconds);
}

String ActuatorClient::getGetRequestFromServer() {
    return client.readStringUntil('\n');
}

int ActuatorClient::getSubstringPositionInString(String string, String subString) {
    return string.indexOf(subString);
}

char ActuatorClient::getCharacterOfAPositionOfAString(String string, int position_) {
    return string.charAt(position_);
}

int ActuatorClient::castCharToInt(char char_) {
    return char_ - '0';
}

void ActuatorClient::turnLedsOnAndOffBasedOnGetRequest(String getRequestFromServer) {
    int redIndex = getSubstringPositionInString(getRequestFromServer, "R=") + 2;
    int yellowIndex = getSubstringPositionInString(getRequestFromServer, "Y=") + 2;
    int whiteIndex = getSubstringPositionInString(getRequestFromServer, "W=") + 2;
    int blueIndex = getSubstringPositionInString(getRequestFromServer, "B=") + 2;
    
    char redCharacterValue = getCharacterOfAPositionOfAString(getRequestFromServer, redIndex);
    char yellowCharacterValue = getCharacterOfAPositionOfAString(getRequestFromServer, yellowIndex);
    char whiteCharacterValue = getCharacterOfAPositionOfAString(getRequestFromServer, whiteIndex);
    char blueCharacterValue = getCharacterOfAPositionOfAString(getRequestFromServer, blueIndex);

    int redIntValue = castCharToInt(redCharacterValue);
    int yellowIntValue = castCharToInt(yellowCharacterValue);
    int whiteIntValue = castCharToInt(whiteCharacterValue);
    int blueIntValue = castCharToInt(blueCharacterValue);
    
    redLed->turnOff();
    yellowLed->turnOff();
    whiteLed->turnOff();
    blueLed->turnOff();
    
    if (blueIntValue == 1) {
        blueLed->turnOn();
    }

    if (whiteIntValue == 1) {
        whiteLed->turnOn();
    }

    if (yellowIntValue == 1) {
        yellowLed->turnOn();
    }

    if (redIntValue == 1) {
        redLed->turnOn();
    }
}
