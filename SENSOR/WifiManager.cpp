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

IPAddress WifiManager::getIpAddressOfTheDevice() {
    return WiFi.localIP();
}

void WifiManager::connectToWifi() {
    Serial.print("Connecting to: ");
    Serial.print(ssid);
    WiFi.begin(ssid, password);
    while (getWifiConnectionStatus() != WL_CONNECTED) {
        delay(200);
        Serial.print(".");
    }
    Serial.print("\nIP address of the device: ");
    Serial.println(getIpAddressOfTheDevice());
}
