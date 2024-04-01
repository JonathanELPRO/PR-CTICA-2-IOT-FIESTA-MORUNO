#include "WifiManager.h"
#include "ActuatorClient.h"
const char *wifiSSID = "TERAN";
const char *wifiPassword = "GJJ2023mg";
const char *serverAddress = "192.168.1.10";
const int serverPort = 7001;
ActuatorClient *actuatorClient = new ActuatorClient();

void setup() {
    Serial.begin(9600);
    WifiManager *wifiManager = new WifiManager(wifiSSID, wifiPassword);
    wifiManager->connectToWifi();
}

void loop() {
    Serial.print("Connecting to: ");
    Serial.println(serverAddress);
    actuatorClient->connectWithServer(serverAddress, serverPort);
    actuatorClient->sendGetToServer();
    actuatorClient->waitForResponseFromTheServer(500);
    actuatorClient->doSomethingBasedOnGetRequest();
    Serial.println("Closing connection.");
    actuatorClient->terminateTheConnection();
    actuatorClient->waitMilliseconds(1000);
}
