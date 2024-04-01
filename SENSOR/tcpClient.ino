#include "WifiManager.h"
#include "SensorClient.h"
const char *wifiSSID = "TERAN";
const char *wifiPassword = "GJJ2023mg";
const char *serverAddress = "192.168.1.10";
const int serverPort = 7001;
SensorClient *sensorClient = new SensorClient();



void setup() {
    Serial.begin(115200);
    WifiManager *wifiManager = new WifiManager(wifiSSID, wifiPassword);
    wifiManager->connectToWifi();
}

void loop() {
    float temperatureRead = sensorClient->getTemperatureFromEnvironmentInCelsius();
    Serial.println(temperatureRead);
    Serial.print("Connecting to: ");
    Serial.println(serverAddress);
    sensorClient->connectWithServer(serverAddress, serverPort);
    String set = "SET " + String(temperatureRead) + "\n";
    sensorClient->sendSetToServer(set);
    Serial.println("Closing connection.");
    sensorClient->terminateTheConnection();
    sensorClient->waitMilliseconds(1500);
}
