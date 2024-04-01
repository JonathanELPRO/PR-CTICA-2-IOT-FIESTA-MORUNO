#include "Led.h"

Led::Led(byte ledPin, String color) {
    this->ledPin = ledPin;
    this->color = color;
    pinMode(ledPin, OUTPUT);
}

Led::~Led() {
}

void Led::turnOn() {
    digitalWrite(ledPin, HIGH);
}

void Led::turnOff() {
    digitalWrite(ledPin, LOW);
}

void Led::blinkWithFrequency(float seconds) {
    float milliseconds = seconds * 1000;
    turnOn();
    delay(milliseconds);
    turnOff();
    delay(milliseconds);
}

int Led::getSubstringPositionInString(String string, String subString) {
    return string.indexOf(subString);
}

char Led::getCharacterOfAPositionOfAString(String string, int position_) {
    return string.charAt(position_);
}

bool Led::castCharToBool(char character) {
    return character != '0';
}

void Led::setStateInBaseGetRequests(String getRequestFromServer) {
    
    char characterValue = getCharacterOfAPositionOfAString(getRequestFromServer, getSubstringPositionInString(getRequestFromServer, color) + 2);
    this->state = castCharToBool(characterValue);
}

bool Led::getState() {
    return state;
}
