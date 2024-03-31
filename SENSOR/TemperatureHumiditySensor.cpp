#include "TemperatureHumiditySensor.h"

TemperatureHumiditySensor::TemperatureHumiditySensor(int pin, int type) {
    this->pin = pin;
    this->type = type;
    dht = new DHT(this->pin, this->type);
}

TemperatureHumiditySensor::~TemperatureHumiditySensor() {
    delete dht;
}

void TemperatureHumiditySensor::configureInitialization() {
    dht->begin();
}

float TemperatureHumiditySensor::getHumidityFromEnvironment() {
    return dht->readHumidity();
}

float TemperatureHumiditySensor::getTemperatureFromEnvironmentInCelsius() {
    return dht->readTemperature(); 
}

float TemperatureHumiditySensor::getTemperatureFromEnvironmentInFahrenheit() {
    return dht->readTemperature(true); 
}
