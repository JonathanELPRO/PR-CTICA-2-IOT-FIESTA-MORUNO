#include "SensorClient.h"

SensorClient::SensorClient() {
}

SensorClient::~SensorClient() {
}

bool SensorClient::connectWithServer(const char* serverAddress, const int serverPort) {
    return client.connect(serverAddress, serverPort);
}

const char* SensorClient::getPointerToConstantCharacterArray(String& string) {
    return string.c_str();
}

void SensorClient::sendSetToServer(String set) {
    client.print(getPointerToConstantCharacterArray(set));
}

void SensorClient::terminateTheConnection() {
    client.stop();
}

unsigned long SensorClient::getTimeElapsedSinceESPStarted() {
    return millis();
}

void SensorClient::waitMilliseconds(int milliseconds) {
    unsigned long previousTimeElapsedSinceESPStarted = getTimeElapsedSinceESPStarted();
    while (getTimeElapsedSinceESPStarted() - previousTimeElapsedSinceESPStarted < milliseconds);
}
