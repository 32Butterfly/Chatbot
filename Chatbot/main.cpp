/*
ChatBot version 3 by Evaldas Dmitrisin MIF VU Information Technologies 1st year 3rd group.
Object-oriented programming class project of a chatbot which interacts with the user.

V3 CHANGELOG
 - Remade the whole code with classes.
 - Added ErrorHandler for custom error messages (this is a change for V3.1)
 - Made the code way more modular.
 - Fixed the bug in agreeing to play a game when user had a rough day.
 - Added extra functionality (playMath).
 - Added try/catch blocks to handle unexpected errors.
 - Added the changelog and comments.
 - Various other fixes.
*/

#include <iostream>
#include "UserInput.h"
#include "User.h"
#include "ChatBot.h"

int main() {
  std::cout << "\t\t  Chatbot v3\n" << std::endl;

  try {
    User user;
    user.setUsername(); //Prompt the user to set their username

    ChatBot chatBot;
    chatBot.startChatBot(user.getUsername()); // Start the chatbot and greet the user

    while (true) {
      // Ask the user about their day and store their response
      bool userFeelings = chatBot.askAboutUserDay(user.getUsername());

      // If the user had a good day, ask about hobbies; otherwise, play trivia
      if (userFeelings) {
        chatBot.askAboutHobbies(user.getUsername());
      } else {
          chatBot.playTrivia(user.getUsername());
      }

      // Prompt the user to restart or exit the conversation
      chatBot.promptRestartOrExit(user.getUsername());
      }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
