#include "LedController.h"

LedController::LedController() {
    setLedState(LedColor::RED, false);
    setLedState(LedColor::YELLOW, false);
    setLedState(LedColor::WHITE, false);
    setLedState(LedColor::BLUE, false);
}

LedController::~LedController() {
}

void LedController::setLedState(LedColor color, bool state) {
    statesOfLeds[color] = state;
}

bool LedController::getLedState(LedColor color) {
    std::map<LedColor, bool>::iterator keyValuePair = statesOfLeds.find(color);
    if (keyValuePair != statesOfLeds.end()) {
        return keyValuePair->second;
    }
    return false;
}

void LedController::setAllLedStatesToFalse() {
    setLedState(LedColor::RED, false);
    setLedState(LedColor::YELLOW, false);
    setLedState(LedColor::WHITE, false);
    setLedState(LedColor::BLUE, false);
}
