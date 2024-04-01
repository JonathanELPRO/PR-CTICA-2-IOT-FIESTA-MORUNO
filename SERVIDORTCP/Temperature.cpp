#include "Temperature.h"

Temperature::Temperature(double value) {
    this->value = value;
}

double* Temperature::getPointerValue() {
    return &value;
}

double Temperature::getValue() {
    return value;
}

void Temperature::setValue(double value) {
    this->value = value;
}
