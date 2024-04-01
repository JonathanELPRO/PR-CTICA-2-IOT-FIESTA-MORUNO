#include <WiFi.h>
#include "TemperatureHumiditySensor.h"
#define DHTPIN 21

class SensorClient {
private:
    WiFiClient client;
    TemperatureHumiditySensor* temperatureHumiditySensor;
public:
    SensorClient();
    ~SensorClient();
    void connectWithServer(const char* serverAddress, const int serverPort);
    const char* getPointerToConstantCharacterArray(String& string);
    void sendSetToServer(String set);
    void terminateTheConnection();
    unsigned long getTimeElapsedSinceESPStarted();
    void waitMilliseconds(int milliseconds);
    float getTemperatureFromEnvironmentInCelsius();
};
