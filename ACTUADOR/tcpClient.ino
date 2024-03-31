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
    if (!actuatorClient->connectWithServer(serverAddress, serverPort)) {
        Serial.println("Connection failed");
        return;
    }

    String get = "GET\n";
    actuatorClient->sendGetToServer(get);
    actuatorClient->waitForResponseFromTheServer(500);

    if (actuatorClient->thereIsDataToBeReadFromTheServer() > 0) {
        String getRequestFromServer = actuatorClient->getGetRequestFromServer();
        // String line = "R=0, Y=0, W=0, B=1";
        actuatorClient->turnLedsOnAndOffBasedOnGetRequest(getRequestFromServer);
    }

    Serial.println("Closing connection.");
    actuatorClient->terminateTheConnection();
    actuatorClient->waitMilliseconds(1000);
}
