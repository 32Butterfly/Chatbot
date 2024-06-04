#include "ErrorHandler.h"

// Implement the custom exception messages
const std::string ErrorHandler::MSG_USERNAME_TOO_LONG = "Username is too long.";
const std::string ErrorHandler::MSG_USERNAME_TOO_SHORT = "Username is too short.";
const std::string ErrorHandler::MSG_EMPTY_USERNAME = "Username cannot be empty.";
const std::string ErrorHandler::MSG_EMPTY = "Input cannot be empty.";
const std::string ErrorHandler::MSG_TOO_LONG = "Input is too long.";
const std::string ErrorHandler::MSG_CONTAINS_NON_DIGIT = "Input contains non-digit characters.";
const std::string ErrorHandler::MSG_INCORRECT = "Please type either 'exit' or 'start over'";
const std::string ErrorHandler::MSG_NOT_YES_OR_NO = "Please type either 'yes' or 'no'";

void ErrorHandler::validateUsername(const std::string& username) {
  if (username.empty()) {
    throw ChatbotException(MSG_EMPTY_USERNAME);
  }
  if (username.length() > 20) {
    throw ChatbotException(MSG_USERNAME_TOO_LONG);
  }
  if (username.length() < 3) {
    throw ChatbotException(MSG_USERNAME_TOO_SHORT);
  }
}

void ErrorHandler::validateResponse(std::string& response){
  if (response.empty()) {
    throw ChatbotException(MSG_EMPTY);
  }
  else if (response.length() >= 30) {
    throw ChatbotException(MSG_TOO_LONG);
  }
}

void ErrorHandler::validateDigits(std::string& input) {
  for (char c : input) { // Iterate through each character in the input
    if (!std::isdigit(c)) { // Check if the character is not a digit
      throw ChatbotException(MSG_CONTAINS_NON_DIGIT);
    }
  }
}

void ErrorHandler::restartOrStartOver(std::string& response){
  if (response.find("exit") == std::string::npos && response.find("start over") == std::string::npos && ! response.empty()){
    throw ChatbotException(MSG_INCORRECT);
  }
}

void ErrorHandler::validateYesOrNo (std::string& response){
  if (response != "no" && response != "yes" && ! response.empty()){
    throw ChatbotException(MSG_NOT_YES_OR_NO);
  }
}
