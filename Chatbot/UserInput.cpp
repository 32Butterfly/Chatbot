#include "UserInput.h"
#include <iostream>
#include <stdexcept>
#include <algorithm>

std::string UserInput::getUserInput(const std::string& username) {
  std::string response;
  std::cout << username << ":  ";
  std::getline(std::cin, response);
  std::transform(response.begin(), response.end(), response.begin(), ::tolower); // Convert input to lowercase

  return response;
}

std::string UserInput::getResponse() {
  return response;
}

void UserInput::setResponse(const std::string& username) {
  ErrorHandler errorHandler;
  try {
    this->response = getUserInput(username);
    errorHandler.validateResponse(response);
  }
  catch (const ChatbotException& e) {
    // Handle ChatbotException
    std::cerr << "Error: " << e.what() << std::endl;
  }
}
