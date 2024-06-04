#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

#include <exception>
#include <string>

class ChatbotException : public std::exception {
public:
  explicit ChatbotException(const std::string& message) : msg(message) {}
  const char* what() const noexcept override {
      return msg.c_str();
  }

private:
  std::string msg;
};

class ErrorHandler {
public:
  static const std::string MSG_USERNAME_TOO_LONG;
  static const std::string MSG_USERNAME_TOO_SHORT;
  static const std::string MSG_EMPTY_USERNAME;
  static const std::string MSG_EMPTY;
  static const std::string MSG_TOO_LONG;
  static const std::string MSG_CONTAINS_NON_DIGIT;
  static const std::string MSG_INCORRECT;
  static const std::string MSG_NOT_YES_OR_NO;

  void validateUsername(const std::string& username);
  void validateResponse(std::string& response);
  void validateDigits(std::string& response);
  void restartOrStartOver(std::string& response);
  void validateYesOrNo (std::string& response);
};

#endif // ERROR_HANDLER_H
