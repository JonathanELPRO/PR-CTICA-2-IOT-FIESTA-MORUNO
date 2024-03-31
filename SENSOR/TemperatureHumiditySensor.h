#include "DHT.h"

class TemperatureHumiditySensor {
private:
    int pin;
    int type;
    DHT *dht;

public:
    TemperatureHumiditySensor(int pin, int type);
    ~TemperatureHumiditySensor();
    void configureInitialization();
    float getHumidityFromEnvironment();
    float getTemperatureFromEnvironmentInCelsius();
    float getTemperatureFromEnvironmentInFahrenheit();
};
