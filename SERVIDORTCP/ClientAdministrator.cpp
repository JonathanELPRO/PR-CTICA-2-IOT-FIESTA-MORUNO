#include "ClientAdministrator.h"

const char* SET = "SET";

ClientAdministrator::ClientAdministrator(int clientSocket) {
    this->clientSocket = clientSocket;
}

ClientAdministrator::~ClientAdministrator() {
}

void ClientAdministrator::updateLedsStatusFromTemperature(bool* redLed, bool* yellowLed, bool* whiteLed, bool* blueLed, double* temperature) {
    *redLed = *yellowLed = *whiteLed = *blueLed = false;

    if (*temperature >= -10.0 && *temperature < 0.0) {
        *blueLed = true;
    } else if (*temperature >= 0.0 && *temperature < 15.0) {
        *whiteLed = true;
    } else if (*temperature >= 15.0 && *temperature < 25.0) {
        *yellowLed = true;
    } else if (*temperature >= 25.0 && *temperature < 50) {
        *redLed = true;
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

char* ClientAdministrator::getTheGetRequestMessage(bool* redLed, bool* yellowLed, bool* whiteLed, bool* blueLed) {
    char* messageGet = new char[20];
    std::memset(messageGet, 0, 20);
    std::sprintf(messageGet, "R=%d, Y=%d, W=%d, B=%d", *redLed, *yellowLed, *whiteLed, *blueLed);
    return messageGet;
}

int ClientAdministrator::getTheSizeOfString(char* messageGet) {
    return std::strlen(messageGet);
}

void ClientAdministrator::sendGetMessageToClient(char* messageGet) {
    send(clientSocket, messageGet, getTheSizeOfString(messageGet), 0);
}

void ClientAdministrator::performTheSetProtocol(char* buffer, double* temperature, bool* redLed, bool* yellowLed, bool* whiteLed, bool* blueLed) {
    extractTemperatureFromBufferInVariable(buffer, temperature);
    std::cout << "Temperature stored: " << *temperature << std::endl;
    updateLedsStatusFromTemperature(redLed, yellowLed, whiteLed, blueLed, temperature);
}

void ClientAdministrator::performTheGetProtocol(bool* redLed, bool* yellowLed, bool* whiteLed, bool* blueLed) {
    char* messageGet = getTheGetRequestMessage(redLed, yellowLed, whiteLed, blueLed);
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

void ClientAdministrator::putSetOrSendGet(char* buffer, char* nameMethod, double* temperature, bool* redLed, bool* yellowLed, bool* whiteLed, bool* blueLed) {
    int numberOfBytesOfMessageReceivedByTheClient;

    while ((numberOfBytesOfMessageReceivedByTheClient = getNumberOfBytesOfMessageReceivedByTheClient(buffer)) > 0) {
        std::cout << "Received: " << buffer << std::endl;
        identifyTheTypeOfMethod(buffer, nameMethod);
        std::cout << "Method: " << nameMethod << std::endl;

        if (stringsEquals(nameMethod, SET)) {
            performTheSetProtocol(buffer, temperature, redLed, yellowLed, whiteLed, blueLed);
        } else {
            performTheGetProtocol(redLed, yellowLed, whiteLed, blueLed);
        }

        clearString(buffer, BUFFER_SIZE);
    }
    if (numberOfBytesOfMessageReceivedByTheClient < 0) {
        perror("read");
    }

    endConnectionWithClient();
}
