#include <WiFi.h>

class WifiManager {
private:
    const char* ssid;
    const char* password;

public:
    WifiManager(const char* ssid, const char* password);
    ~WifiManager();
    int getWifiConnectionStatus();
    IPAddress getIpAddressOfTheDevice();
    void connectToWifi();
};
