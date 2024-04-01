#include "ClientAdministrator.h"

const char* SET = "SET";

ClientAdministrator::ClientAdministrator(int clientSocket) {
    this->clientSocket = clientSocket;
}

ClientAdministrator::~ClientAdministrator() {}

void ClientAdministrator::updateLedsStatusFromTemperature(LedController* ledController, Temperature* temperature) {
    ledController->setAllLedStatesToFalse();
    if (temperature->getValue() >= -10.0 && temperature->getValue() < 0.0) {
        ledController->setLedState(LedColor::BLUE, true);
    } else if (temperature->getValue() >= 0.0 && temperature->getValue() < 15.0) {
        ledController->setLedState(LedColor::WHITE, true);
    } else if (temperature->getValue() >= 15.0 && temperature->getValue() < 25.0) {
        ledController->setLedState(LedColor::YELLOW, true);
    } else if (temperature->getValue() >= 25.0 && temperature->getValue() < 50) {
        ledController->setLedState(LedColor::RED, true);
    }
}

int ClientAdministrator::getNumberOfBytesOfMessageReceivedByTheClient(char* buffer) {
    return read(clientSocket, buffer, BUFFER_SIZE);
}

char* ClientAdministrator::getPointerToCharacterFromString(char* string, char character) {
    return std::strchr(string, character);
}

size_t ClientAdministrator::getTheNumberOfCharactersBetweenTwoCharacterPointers(char* pointerChar1, char* pointerChar2) {
    return pointerChar1 - pointerChar2;
}

void ClientAdministrator::copySubstringInOtherString(char* string, char* string2, size_t numberOfCharactersToCopy) {
    std::strncpy(string, string2, numberOfCharactersToCopy);
    string[numberOfCharactersToCopy] = '\0';
}

void ClientAdministrator::copyStringInOtherString(char* copiedString, char* stringToCopy) {
    std::strcpy(copiedString, stringToCopy);
}

void ClientAdministrator::identifyTheTypeOfMethod(char* buffer, char* nameMethod) {
    char* ptr_space = getPointerToCharacterFromString(buffer, ' ');
    if (ptr_space != nullptr) {
        size_t numberOfCharactersBetweenTwoCharacterPointers = getTheNumberOfCharactersBetweenTwoCharacterPointers(ptr_space, buffer);
        copySubstringInOtherString(nameMethod, buffer, numberOfCharactersBetweenTwoCharacterPointers);
    } else {
        copyStringInOtherString(nameMethod, buffer);
    }
}

bool ClientAdministrator::stringsEquals(char* string1, const char* string2) {
    return std::strcmp(string1, string2) == 0;
}

void ClientAdministrator::extractTemperatureFromBufferInVariable(char* buffer, double* temperature) {
    std::sscanf(buffer, "SET %lf", temperature);
}

char* ClientAdministrator::getTheGetRequestMessage(LedController* ledController) {
    char* messageGet = new char[20];
    std::memset(messageGet, 0, 20);
    std::sprintf(messageGet, "R=%d, Y=%d, W=%d, B=%d", ledController->getLedState(LedColor::RED), ledController->getLedState(LedColor::YELLOW), ledController->getLedState(LedColor::WHITE), ledController->getLedState(LedColor::BLUE));
    return messageGet;
}

int ClientAdministrator::getTheSizeOfString(char* messageGet) {
    return std::strlen(messageGet);
}

void ClientAdministrator::sendGetMessageToClient(char* messageGet) {
    send(clientSocket, messageGet, getTheSizeOfString(messageGet), 0);
}

double* ClientAdministrator::getPointerFromDouble(double &Double) {
    return &Double;
} 

void ClientAdministrator::performTheSetProtocol(LedController* ledController, MessageHandler* messageHandler, Temperature* temperature) {
    extractTemperatureFromBufferInVariable(messageHandler->getBuffer(), temperature->getPointerValue());
    std::cout << "Temperature stored: " << temperature->getValue() << std::endl;
    updateLedsStatusFromTemperature(ledController, temperature);
}

void ClientAdministrator::performTheGetProtocol(LedController* ledController) {
    char* messageGet = getTheGetRequestMessage(ledController);
    sendGetMessageToClient(messageGet);
    std::cout << "Echoed back: " << messageGet << std::endl;
    delete[] messageGet;
}

void ClientAdministrator::clearString(char* string, int sizeString) {
    std::memset(string, 0, sizeString);
}

void ClientAdministrator::endConnectionWithClient() {
    close(clientSocket);
}

void ClientAdministrator::identifyAndProcessMethod(LedController* ledController, MessageHandler* messageHandler, Temperature* temperature) {
    identifyTheTypeOfMethod(messageHandler->getBuffer(), messageHandler->getNameMethod());
    std::cout << "Method: " << messageHandler->getNameMethod() << std::endl;

    if (stringsEquals(messageHandler->getNameMethod(), SET)) {
        performTheSetProtocol(ledController, messageHandler, temperature);
    } else if (!stringsEquals(messageHandler->getNameMethod(), SET)) {
        performTheGetProtocol(ledController);
    }
}

void ClientAdministrator::processReceivedMessage(LedController* ledController, MessageHandler* messageHandler, Temperature* temperature) {
    std::cout << "Received: " << messageHandler->getBuffer() << std::endl;
    identifyAndProcessMethod(ledController, messageHandler, temperature);
}

void ClientAdministrator::putSetOrSendGet(LedController* ledController, MessageHandler* messageHandler, Temperature* temperature) {
    int numberOfBytesOfMessageReceivedByTheClient;

    while ((numberOfBytesOfMessageReceivedByTheClient = getNumberOfBytesOfMessageReceivedByTheClient(messageHandler->getBuffer())) > 0) {
        processReceivedMessage(ledController, messageHandler, temperature);
        clearString(messageHandler->getBuffer(), BUFFER_SIZE);
    }
    if (numberOfBytesOfMessageReceivedByTheClient < 0) {
        perror("read");
    }

    endConnectionWithClient();
}
