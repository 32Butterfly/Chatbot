#include "ChatBot.h"
#include <iostream>
#include <stdexcept>
#include <ctime>
#include <algorithm>
#include "UserInput.h"
#include "ErrorHandler.h"

ChatBot::ChatBot(std::string username) {
  srand(static_cast<unsigned int>(time(0)));
  greetUser(username);
}

void ChatBot::greetUser(const std::string& username) const {
  int greetIndex = rand() % greetings.size(); // Generate a random index within the greetings vector
  std::cout << CHATNAME << ":  " << greetings[greetIndex] << " my name is " << CHATNAME
  << " nice to meet you " << username << "!" << std::endl;
}

bool ChatBot::askAboutUserDay(const std::string& username) {
  std::cout << CHATNAME << ":  " << "How was your day so far? (good/bad)" << std::endl;
  UserInput userInput;
  userInput.setResponse(username);
  std::string response = userInput.getResponse();
  endConversation(response, username);
  bool userFeelings = howUserIsFeeling(response, username);

  return userFeelings; // Return the user's feelings [TRUE for happy]
}

bool ChatBot::howUserIsFeeling(std::string& response, const std::string& username) const {
  while(true){
    for (std::string negativeWord : negativeWords) {
      if (response.find(negativeWord) != std::string::npos) {
        return false; // User is not feeling good
      }
    }

  for (std::string positiveWord : positiveWords) {
    if (response.find(positiveWord) != std::string::npos) {
      return true; // User is feeling good
      }
    }

    // If the response is not empty, prompt the user to clarify
    if(!response.empty()){
      std::cout << CHATNAME << ":  " << "Sorry, I don't understand. Could you say how it was did it go well or not that well?"
      << std::endl;
    }

    UserInput userInput;
    userInput.setResponse(username);
    response = userInput.getResponse();
    endConversation(response, username);
  }
}

//This is the route if you had a bad day
bool ChatBot::gameMenu(const std::string& username) {
  std::cout << CHATNAME << ":  " << "I'm sorry to hear that. Would you like to play a game to cheer up?" << std::endl;
  UserInput userInput;
  userInput.setResponse(username);
  std::string response = userInput.getResponse();
  bool agrees = validateYesOrNoResponse(response, username);

  if (agrees){
    std::cout << CHATNAME << ":  " << "I'm happy to hear that " << username << std::endl;
    std::cout << CHATNAME << ":  " << "Here is the game I've been programmed to know" << std::endl;
    std::cout << "[1] Quiz" << std::endl;
  }
  else{
    std::cout << CHATNAME << ":  " << "I'm sad that you don't want to play but I understand :c" << std::endl;
  }

  return agrees; // Return true indicating the user agreed to play a game
}

 void ChatBot::menuChooseValidation(const std::string& username) {
  UserInput userInput;
  userInput.setResponse(username);
  std::string response = userInput.getResponse();
  int incorrectInput = 0;

  // Continue looping until the user selects option 1
  while (response != "1"){
    endConversation(response, username);
    incorrectInput++;

    failedMenuChoice(incorrectInput); //Display messages depending on how many times user failed

    // Check if the user has selected option 1
    if (response == "1"){
      break; // Break out of the loop if the user selects option 1
    }

    userInput.setResponse(username);
    response = userInput.getResponse();
  }
}

 void ChatBot::failedMenuChoice(int inccorectInput){
  // Provide feedback based on how many times the user input the incorrect input
  if (inccorectInput == 1) {
      std::cout << CHATNAME << ":  " << "Please be kind and input 1 to select the game" << std::endl;
  }
  else if (inccorectInput == 2) {
    std::cout << CHATNAME << ":  " << "Okay this isn't funny just press number 1 and press enter" << std::endl;
  }
  else { // If the user repeatedly provides incorrect inputs, display a final message and exit the program
    std::cout << CHATNAME << ":  " << "Wow you think you're so funny! Just get out of here we could have"
    << "played but you decided to ruin it" << std::endl;
    std::cout << "???" << ":  " << "You have angered the bot too much and thus he shut down which is supposed"
    << "to happen so just restart him" << std::endl;
        exit(0);
  }
}

void ChatBot::playTrivia(const std::string& username) {
  if (gameMenu(username)){ // Check if the user wants to play a game
    menuChooseValidation(username);
    trivia(username, starterTriviaQuestions, starterTriviaAnswers);

    // Play trivia based on the user's performance
    if (triviaScore >= 2){
      trivia(username, harderTriviaQuestions, harderTriviaAnswers);
    }
    else{
    trivia(username, easierTriviaQuestions, easierTriviaAnswers);
    }

    triviaFeedback();
  }
}

// Trivia game with the user using vectors of questions and their answers that are passed
  void ChatBot::trivia(const std::string& username, const std::vector<std::string>& questions, const std::vector<std::string>& answers) {
  // Loop through each question
  for (std::size_t i = 0; i < questions.size(); ++i) {
    std::cout << CHATNAME << ":  " << "True or false: " << questions[i] << std::endl;
    UserInput userInput;
    userInput.setResponse(username);
    std::string response = userInput.getResponse();
    endConversation(response, username);

    // Ensure the user's response is either "true" or "false"
    while (response != "true" && response != "false") {
      std::cout << CHATNAME << ":  " << "Please type either true or false" << std::endl;
      userInput.setResponse(username);
      response = userInput.getResponse();
      endConversation(response, username);
    }

    // Check if the user's response matches the correct answer
    if (response == answers[i]) {
      std::cout << CHATNAME << ":  " << "Correct! Good job ^^" << std::endl;
      triviaScore++;
    }
    else {
        std::cout << CHATNAME << ":  " << "Incorrect!" << std::endl;
    }
  }
}

void ChatBot::triviaFeedback(){
  //provide feedback based on how many answers were correct
  if (triviaScore > 2) {
    std::cout << CHATNAME << ":  " << "You answered " << triviaScore << "/6 questions which is not bad ^^" << std::endl;
  }
  else if (triviaScore == 6 ){
    std::cout << CHATNAME << ":  " << "Good job you got all of them correctly" << std::endl;
  }
  else {
    botHappiness--;
    std::cout << CHATNAME << ":  " << "Pretty disappointing you only managed to answer " << triviaScore << "/6" << std::endl;
  }
      std::cout << CHATNAME << ":  " << "The game has ended!" << std::endl;
}

//This is the start of the route if you had a good day
bool ChatBot::askIfUserHasHobbies(const std::string& username) {
  std::cout << CHATNAME << ":  " << "I'm happy to hear that :)" << std::endl;
  std::cout << CHATNAME << ":  " << "Is there an interesting hobby you have perhaps? (yes/no)" << std::endl;

  UserInput userInput;
  userInput.setResponse(username);
  std::string response = userInput.getResponse();
  endConversation(response, username);

  return validateYesOrNoResponse(response, username); // Return true if user has hobby, false otherwise
}

bool ChatBot::validateYesOrNoResponse(std::string response, const std::string& username) {
  while (true) {
    try {
      ErrorHandler errorHandler;
      errorHandler.validateYesOrNo(response); //validate whether the response is yes or no

      if (response == "yes" || response == "no") {
        break; //break the loop
      }
    }
    catch (const ChatbotException& e) {
      // Handle ChatbotException
      std::cerr << "Error: " << e.what() << std::endl;
    }

    UserInput userInput;
    userInput.setResponse(username);
    response = userInput.getResponse();
    endConversation(response, username);
  }

  return response == "yes"; // Return true if response is yes, false otherwise
}

void ChatBot::askAboutHobbies(const std::string& username) {
  bool userHasHobby = askIfUserHasHobbies(username); // Check if the user has any hobbies

  if (userHasHobby){ // If the user has a hobby, attempt to guess it
    guessHobby(username);
  }
  // If the user doesn't have a hobby as a punishment for lying play a math game with them
  else{
    playMath(username, mathQuestions, mathAnswers);
    mathScoreFeedback();
  }
}

void ChatBot::guessHobby(const std::string& username) {
  for (std::size_t i = 0; i < hobbies.size(); ++i) {
    std::cout << CHATNAME << ":  " << "Does your hobby happen to be " << hobbies[i] << " yes/no" << std::endl;
    UserInput userInput;
    userInput.setResponse(username);
    std::string response = userInput.getResponse();
    endConversation(response, username);

    // If the user confirms having the hobby, display information about it
    if (validateYesOrNoResponse(response, username)) {
      std::cout << CHATNAME << ":  " << "Your hobby is " << hobbies[i] << ". I'm glad I managed to guess it correctly." << std::endl;
      std::cout << CHATNAME << ":  " << "Fun fact about " << hobbies[i] << ":  " << funFacts[i] << std::endl;
      break; // Exit the loop since the hobby has been guessed
    }

    // Check if the loop has reached the last element of the hobbies vector and if the answer was no display the message
    if (i == hobbies.size() - 1) {
      std::cout << CHATNAME << ":  " << "I'm sorry with my limited knowledge I couldn't guess your hobby shame on me!" << std::endl;
    }
  }
}

void ChatBot::playMath(const std::string& username, const std::vector<std::string>& questions, const std::vector<std::string>& answers) {
  botHappiness--;
  std::cout << CHATNAME << ":  " << "Liar everybody has at least 1 hobby :c" << std::endl;
  std::cout << CHATNAME << ":  " << "As a punishment I will make you solve math equations and judge your skills" << std::endl;

  for (std::size_t i = 0; i < questions.size(); ++i) {
    std::cout << CHATNAME << ":  " << "What is: " << questions[i] << std::endl;
    UserInput userInput;
    userInput.setResponse(username);
    std::string response = userInput.getResponse();
    endConversation(response, username);

    if (!containsOnlyDigits(response)) {
      --i; //i decreases so the same question is asked until the user provides an answer with digits only
    }
    else if (response.empty()){
      --i;
    }
    else{
      // Check if the user's response matches the correct answer
      if (response == answers[i]) {
        std::cout << CHATNAME << ":  " << "Correct!" << std::endl;
        mathScore++;
      }
      else {
        mathIncorrectGuessFeedback(i); //give feedback for incorrect answer
      }
    }
  }
}

bool ChatBot::containsOnlyDigits(std::string& response) {
  try {
    // Check if the character is not a digit
    ErrorHandler errorHandler;
    errorHandler.validateDigits(response);
    return true; // If all characters are digits, return true
  }
  catch (const ChatbotException& e) {
    // Handle ChatbotException
    std::cerr << "Error: " << e.what() << std::endl;
    return false;
  }
}

void ChatBot::mathIncorrectGuessFeedback(int index){
  // Provide feedback based on the question difficulty
  switch(index){
    case 0:
      std::cout << CHATNAME << ":  " << "Incorrect! Really failing on the easiest question?" << std::endl;
      break;
    case 1:
    case 2:
      std::cout << CHATNAME << ":  " << "Incorrect! I guess multiplying isn't your strong point" << std::endl;
      break;
    default:
      std::cout << CHATNAME << ":  " << "Incorrect! This is a little tricky" << std::endl;
      break;
  }
}

void ChatBot::mathScoreFeedback(){
  if (mathScore == 0){
    botHappiness--;
    std::cout << CHATNAME <<":  " << "You didn't even answer 1 correctly how is that even possible?" << std::endl;
  }
  else if (mathScore < 3 && mathScore > 0){
    botHappiness--;
    std::cout << CHATNAME <<":  " << "Only " << mathScore << "/5 really?" << std::endl;
  }
  else if (mathScore < 5 && mathScore >= 3) {
    std::cout << CHATNAME <<":  " << mathScore << "/5 You did fairly well so I forgive you!" << std::endl;
  }
  else{
    botHappiness++;
    std::cout << CHATNAME <<":  " << "WOW a perfect score (you used a calculator) but still good!" << std::endl;
  }
}

void ChatBot::promptRestartOrExit(const std::string& username) {
  while(true){
    std::string response;
    std::cout << CHATNAME << ":  " << "Would you like to start over the conversation or exit?" << std::endl;
    UserInput userInput;
    userInput.setResponse(username);
    response = userInput.getResponse();

    try{
      ErrorHandler errorHandler;
      // Check if the user's response indicates a restart or start over
      errorHandler.restartOrStartOver(response);

      if (response == "exit") {
        endConversation("bye", username);
      }
      else if (response.find("start over") != std::string::npos) {
          break;
      }
    }

    catch (const ChatbotException& e) {
      // Handle ChatbotException
      std::cerr << "Error: " << e.what() << std::endl;
    }
  }
}

void ChatBot::endConversation(const std::string& response, const std::string& username) const {
   if (response.find("bye") != std::string::npos) {
    // Respond differently based on the current bot's happiness level
    switch (botHappiness) {
      case HAPPY_EXIT_HIGH:
      case HAPPY_EXIT_LOW:
        std::cout << CHATNAME << ":  " << "Goodbye " << username << "! Have a great day!" << std::endl;
        exit(0);
      case NEUTRAL_EXIT:
        std::cout << CHATNAME << ":  " << "Bye " << username << "! I hope you have an okay day." << std::endl;
        exit(0);
      default:
        std::cout << CHATNAME << ":  " << "Bye " << username << ". Finally I can have peace and quiet." << std::endl;
        exit(0);
    }
  }
}
