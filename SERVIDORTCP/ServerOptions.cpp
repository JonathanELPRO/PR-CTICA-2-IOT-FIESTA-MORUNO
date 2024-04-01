#include "ServerOptions.h"

ServerOptions::ServerOptions(int additionalOptions) {
    this->additionalOptions = additionalOptions;
}

int ServerOptions::getAdditionalOptions() {
    return additionalOptions;
}
