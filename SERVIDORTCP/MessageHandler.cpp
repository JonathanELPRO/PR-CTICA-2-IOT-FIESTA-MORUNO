#include "MessageHandler.h"

MessageHandler::MessageHandler() {
    std::memset(buffer, 0, BUFFER_SIZE);
    std::memset(nameMethod, 0, NAME_METHOD_SIZE);
}

MessageHandler::~MessageHandler() {
}

int MessageHandler::getSizeOfString(char* string) {
    return sizeof(string);
}

void MessageHandler::setBuffer(char* newBuffer) {
    int newBufferSize = getSizeOfString(newBuffer);
    std::strncpy(buffer, newBuffer, newBufferSize);
    buffer[newBufferSize] = '\0';
}

char* MessageHandler::getBuffer() {
    return buffer;
}

void MessageHandler::setNameMethod(char* newNameMethod) {
    int newNameMethodSize = getSizeOfString(newNameMethod);
    std::strncpy(nameMethod, newNameMethod, newNameMethodSize);
    nameMethod[newNameMethodSize] = '\0';
}

char* MessageHandler::getNameMethod() {
    return nameMethod;
}
