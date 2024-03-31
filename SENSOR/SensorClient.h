#include <WiFi.h>

class SensorClient {
private:
    WiFiClient client;

public:
    SensorClient();
    ~SensorClient();
    bool connectWithServer(const char* serverAddress, const int serverPort);
    const char* getPointerToConstantCharacterArray(String& string);
    void sendSetToServer(String set);
    void terminateTheConnection();
    unsigned long getTimeElapsedSinceESPStarted();
    void waitMilliseconds(int milliseconds);
};
