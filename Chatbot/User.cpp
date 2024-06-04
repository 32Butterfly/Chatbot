#include "User.h"
#include <iostream>
#include <stdexcept>
#include "ErrorHandler.h"

User::User() {}

void User::setUsername() {
  ErrorHandler errorHandler;
  while (true) {
    std::cout << "Enter your desired username (3 to 20 characters): " << std::endl;
    std::cout << "User:  ";
    std::getline(std::cin, username);

    try {
      errorHandler.validateUsername(username); // Validate the username
      break; // Break the loop if validation passes

    }catch (const ChatbotException& e) {
      // Handle MyProjectException
      std::cerr << "Error: " << e.what() << std::endl;
    }
  }
}

std::string User::getUsername() const {
  return username;
}

