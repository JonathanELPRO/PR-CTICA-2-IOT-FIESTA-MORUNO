#include <Arduino.h>

class Led {
private:
    byte ledPin;
    bool state;
    String color;
public:
    Led(byte pinLed, String color);
    ~Led();
    void turnOn();
    void turnOff();
    void blinkWithFrequency(float seconds);
    void setStateIbBaseGetRequests(String getRequestFromServer);
    int getSubstringPositionInString(String string, String subString);
    char getCharacterOfAPositionOfAString(String string, int position_);
    bool castCharToBool(char character);
    void setState(bool state);
    void setStateInBaseGetRequests(String getRequestFromServer);
    bool getState();
};
