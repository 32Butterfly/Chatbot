#ifndef USERINPUT_H
#define USERINPUT_H
#include "ErrorHandler.h"

#include <string>

class UserInput {
private:
    std::string response;
    static std::string getUserInput(const std::string& username);

public:
    std::string getResponse();
    void setResponse(const std::string& username);
};

#endif // USERINPUT_H
