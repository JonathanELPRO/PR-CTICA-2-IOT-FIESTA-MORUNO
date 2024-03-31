#include "WifiManager.h"
#include "TemperatureHumiditySensor.h"
#include "SensorClient.h"

const char *wifiSSID = "TERAN";
const char *wifiPassword = "GJJ2023mg";

#define DHTPIN 21
TemperatureHumiditySensor *temperatureHumiditySensor = new TemperatureHumiditySensor(DHTPIN, DHT22);

const char *serverAddress = "192.168.1.10";
const int serverPort = 7001;

void setup() {
    Serial.begin(115200);
    WifiManager *wifiManager = new WifiManager(wifiSSID, wifiPassword);
    wifiManager->connectToWifi();
    temperatureHumiditySensor->configureInitialization();
}

void loop() {
    float temperatureRead = temperatureHumiditySensor->getTemperatureFromEnvironmentInCelsius();
    Serial.println(temperatureRead);
    Serial.print("Connecting to: ");
    Serial.println(serverAddress);
    SensorClient *sensorClient = new SensorClient();
    if (!sensorClient->connectWithServer(serverAddress, serverPort)) {
        Serial.println("Connection failed");
        return;
    }
    String set = "SET " + String(temperatureRead) + "\n";
    sensorClient->sendSetToServer(set);
    Serial.println("Closing connection.");
    sensorClient->terminateTheConnection();
    sensorClient->waitMilliseconds(1500);
}
