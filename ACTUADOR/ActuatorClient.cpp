#include "ActuatorClient.h"

ActuatorClient::ActuatorClient() {
    redLed = new Led(13, "R");
    yellowLed = new Led(27 ,"Y");
    whiteLed = new Led(26, "W");
    blueLed = new Led(25, "B");
}

ActuatorClient::~ActuatorClient() {
}

void ActuatorClient::connectWithServer(const char* serverAddress, const int serverPort) {
    if (!client.connect(serverAddress, serverPort)) {
        Serial.println("Connection failed");
        return;
    }
}

const char* ActuatorClient::getPointerToConstantCharacterArray(String& string) {
    return string.c_str();
}

void ActuatorClient::sendGetToServer() {
    String get = "GET\n";
    client.print(getPointerToConstantCharacterArray(get));
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

void ActuatorClient::getLedsStatusBasedOnTheGetRequest(String getRequestFromServer) {    
    redLed->setStateInBaseGetRequests(getRequestFromServer);
    yellowLed->setStateInBaseGetRequests(getRequestFromServer);
    whiteLed->setStateInBaseGetRequests(getRequestFromServer);
    blueLed->setStateInBaseGetRequests(getRequestFromServer);
}

void ActuatorClient::turnLedsOnAndOffBasedOnGetRequest(String getRequestFromServer) {
    getLedsStatusBasedOnTheGetRequest(getRequestFromServer);
    redLed->turnOff();
    yellowLed->turnOff();
    whiteLed->turnOff();
    blueLed->turnOff();
    if (blueLed->getState()) {
        blueLed->turnOn();
    }
    else if (whiteLed->getState()) {
        whiteLed->turnOn();
    }
    else if (yellowLed->getState()) {
        yellowLed->turnOn();
    }
    else if (redLed->getState()) {
        redLed->turnOn();
    }
}

void ActuatorClient::doSomethingBasedOnGetRequest() {
    if (thereIsDataToBeReadFromTheServer() > 0) {
        String getRequestFromServer = getGetRequestFromServer();
        turnLedsOnAndOffBasedOnGetRequest(getRequestFromServer);
    }
}
