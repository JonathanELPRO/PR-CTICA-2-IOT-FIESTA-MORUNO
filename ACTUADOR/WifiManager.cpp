#include "WifiManager.h"

WifiManager::WifiManager(const char* ssid, const char* password) {
    this->ssid = ssid;
    this->password = password;
}

WifiManager::~WifiManager() {
}

int WifiManager::getWifiConnectionStatus() {
    return WiFi.status();
}

void WifiManager::getIpAddressOfTheDevice() {
    Serial.print("\nIP address of the device: ");
    Serial.println(WiFi.localIP());
}

void WifiManager::connectToNetwork() {
    Serial.print("Connecting to: ");
    Serial.print(ssid);
    WiFi.begin(ssid, password);
}

void WifiManager::checkConnectionStatus() {
    while (getWifiConnectionStatus() != WL_CONNECTED) {
        delay(200);
        Serial.print(".");
    }
}

void WifiManager::connectToWifi() {
    connectToNetwork();
    checkConnectionStatus();
    getIpAddressOfTheDevice();
}
