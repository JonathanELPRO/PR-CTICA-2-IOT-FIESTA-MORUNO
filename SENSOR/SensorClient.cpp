#include "SensorClient.h"

SensorClient::SensorClient() {
    temperatureHumiditySensor = new TemperatureHumiditySensor(DHTPIN, DHT22);
    temperatureHumiditySensor->configureInitialization();
}

SensorClient::~SensorClient() {
}

void SensorClient::connectWithServer(const char* serverAddress, const int serverPort) {
    if (!client.connect(serverAddress, serverPort)) {
        Serial.println("Connection failed");
        return;
    }
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

float SensorClient::getTemperatureFromEnvironmentInCelsius() {
    return temperatureHumiditySensor->getTemperatureFromEnvironmentInCelsius();
}
