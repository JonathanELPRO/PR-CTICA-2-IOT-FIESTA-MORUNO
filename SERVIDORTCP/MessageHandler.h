#include <cstring>

const int BUFFER_SIZE = 1024;
const int NAME_METHOD_SIZE = 10;

class MessageHandler {
 private:
  char buffer[BUFFER_SIZE];
  char nameMethod[NAME_METHOD_SIZE];

 public:
  MessageHandler();
  ~MessageHandler();
  int getSizeOfString(char* string);
  void setBuffer(char* newBuffer);
  char* getBuffer();
  void setNameMethod(char* newNameMethod);
  char* getNameMethod();
};
