/*
ChatBot version 3 by Evaldas Dmitrišin MIF VU Information Technologies 1st year 3rd group.
Object-oriented programming class project of a chatbot which interacts with the user.

V3 CHANGELOG
 - Remade the whole code with classes.
 - Made the code way more modular.
 - Added extra functionality (playMath).
 - Added try/catch blocks to handle unexpected errors.
 - Added the changelog and comments.
 - Various other fixes.
*/

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <ctime>
#include <algorithm>

using namespace std;

//Error messages for user responses and username
#define MSG_USERNAME_TOO_LONG "Your username is too long"
#define MSG_USERNAME_TOO_SHORT "Your username is too short"
#define MSG_EMPTY_USERNAME "Your username cannot be empty"
#define MSG_EMPTY "Please provide an input"
#define MSG_TOO_LONG "The input is too long. Are you trying to break me perhaps?"
#define MSG_CONTAINS_NON_DIGIT "Response contains non-digit characters"

#define CHATNAME "Chippie"

//Values which determine bots exit message
const int HAPPY_EXIT_HIGH = 5;
const int HAPPY_EXIT_LOW = 4;
const int NEUTRAL_EXIT = 3;

// Class representing user input handling
class UserInput {
  private:
    string response;

    // Static method to get user input with validation
    static string getUserInput(const string& username) {
      string response;
      cout << username << ":  ";
      getline(cin, response);
      transform(response.begin(), response.end(), response.begin(), ::tolower); // Convert input to lowercase

      if (response.empty()) {
        throw invalid_argument (MSG_EMPTY);
      }
      if (response.length() >= 30) {
        throw invalid_argument (MSG_TOO_LONG);
      }
      return response;
    }

  public:
    string getResponse() const {
      return response;
    }

    void setResponse(const string& username) {
      try {
        this->response = getUserInput(username);
      }
      catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
      }
    }
};

// Class representing a user
class User {
private:
  string username;

public:
  User() {}

  void setUsername() {
    while (true) {
      cout << "Enter your desired username (3 to 20 characters): " << endl;
      cout << "User:  ";
      getline(cin, username);

      try {
        validateUsername(username); // Validate the username
        break; // Break the loop if validation passes
      }
      catch(const exception& e) {
        cout << "Error: " << e.what() << endl;
      }
    }
    this->username = username;
  }

  string getUsername() const {
    return username;
  }

private:
  // Method to validate the username
  void validateUsername(const string& username) const {
    if (username.empty()) {
        throw invalid_argument(MSG_EMPTY_USERNAME);
    } else if (username.length() < 3) {
        throw invalid_argument(MSG_USERNAME_TOO_SHORT);
    } else if (username.length() > 20) {
        throw invalid_argument(MSG_USERNAME_TOO_LONG);
    }
  }
};

class ChatBot {
private:
  vector<string> greetings = {"Hello", "Hi", "Hey", "Greetings"};
  vector<string> negativeWords = {"bad", "not good", "terrible", "awful", "horrible", "not the best", "disappointing"};
  vector<string> positiveWords = {"good", "decent", "okay", "amazing", "really good", "splendid", "nice"};
  vector<string> happyResponses = {"yes", "sure", "okay", "why not", "of course", "yea", "ofcourse"};
  vector<string> hobbies = {"music", "sports", "gaming", "hiking", "reading"};
  vector<string> funFacts = {
    "Listening to music can improve mood and reduce stress levels.",
    "Regular participation in sports improves cardiovascular health and overall fitness.",
    "Gaming can improve problem-solving skills and enhance cognitive abilities.",
    "Hiking in nature can reduce negative thoughts and improve mental well-being.",
    "Reading can improve empathy and reduce the risk of cognitive decline."};
  vector<string> starterTriviaQuestions ={
    "There are 8 planets in our solar system",
    "An ant can't lift more than 3,000 times its body weight",
    "C++ was originally Called The New C"};
  vector<string> starterTriviaAnswers = { "true", "false", "true"};
  vector<string> harderTriviaQuestions= {
    "Blue eyes are newer to the human race than pottery",
    "Trees existed before sharks",
    "Matches were invented before lighters"};
  vector<string> harderTriviaAnswers = { "true", "false", "true"};
  vector<string> easierTriviaQuestions = {
    "Mount Everest is the tallest mountain in the world",
    "Vatican City is the smallest country in the world",
    "An octopus has seven hearts"};
  vector<string> easierTriviaAnswers = {"false", "true", "false"};
  vector<string> mathQuestions = {
    "20 + 5", "8 * 8", "32 * 47", "3 * (5 + 4)^2 - 100",
    "(8 * 4) + (67 + 98) - (3^2 * 2)"};
  vector<string> mathAnswers = {"25", "64", "1504", "143", "179"};
  int botHappiness = HAPPY_EXIT_HIGH;
  int triviaScore = 0;
  int mathScore = 0;

public:
  // Constructor to initialize the random seed
  ChatBot() {
    srand(static_cast<unsigned int>(time(0)));
  }

  void startChatBot(string username){
    greetUser(username);
  }

  bool askAboutUserDay(const string& username) {
    cout << CHATNAME << ":  " << "How was your day so far? (good/bad)" << endl;
    UserInput userInput;
    userInput.setResponse(username);
    string response = userInput.getResponse();
    endConversation(response, username);
    bool userFeelings = howUserIsFeeling(response, username);

    return userFeelings; // Return the user's feelings [TRUE for happy]
  }

  void playTrivia(string username){
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

      //provide feedback based on how many answers were correct
      if (triviaScore > 2) {
        cout << CHATNAME << ":  " << "You answered " << triviaScore << "/6 questions which is not bad ^^" << endl;
      }
      else if (triviaScore == 6 ){
        cout << CHATNAME << ":  " << "Good job you got all of them correctly" << endl;
      }
      else {
        botHappiness--;
        cout << CHATNAME << ":  " << "Pretty disappointing you only managed to answer " << triviaScore << "/6" << endl;
      }
      cout << CHATNAME << ":  " << "The game has ended!" << endl;
    }
  }

  void askAboutHobbies(const string& username){
    bool userHasHobby = askIfUserHasHobbies(username); // Check if the user has any hobbies

    if (userHasHobby){ // If the user has a hobby, attempt to guess it
      guessHobby(username);
    }
    // If the user doesn't have a hobby as a punishment for lying play a math game with them
    else{
      playMath(username, mathQuestions, mathAnswers);
      if (mathScore < 3){
        botHappiness--;
        cout << CHATNAME <<":  " << "Only " << mathScore << "/5 really?" << endl;
      }
      else if (mathScore < 5 && mathScore >= 3) {
        cout << CHATNAME <<":  " << mathScore << "/5 You did fairly well so I forgive you!" << endl;
      }
      else{
        botHappiness++;
        cout << CHATNAME <<":  " << "WOW a perfect score (you used a calculator) but still good!" << endl;
      }
    }
  }

  void promptRestartOrExit(const string& username) {
    string response;
    cout << CHATNAME << ":  " << "Would you like to start over the conversation or exit?" << endl;
    UserInput userInput;
    userInput.setResponse(username);
    response = userInput.getResponse();

    while (response.find("exit") == string::npos && response.find("start over") == string::npos) {
      if (response.find("bye") != string::npos){
        endConversation("bye", username);
        break;
      }

      cout << CHATNAME << ":  " << "Please type either 'exit' or 'start over'" << endl;
      userInput.setResponse(username);
      response = userInput.getResponse();
    }

    if (response == "exit" || response.find("bye") != string::npos) {
      endConversation("bye", username);
    }
  }

private:
  // Greet the user with a random greeting message
  void greetUser(const string& username) const {
    int greetIndex = rand() % greetings.size(); // Generate a random index within the greetings vector
    cout << CHATNAME << ":  " << greetings[greetIndex] << " my name is " << CHATNAME
    << " nice to meet you " << username << "!" << endl;
  }

  // Present the game menu and ask the user if they want to play a game
  bool gameMenu(const string& username) const {
    cout << CHATNAME << ":  " << "I'm sorry to hear that. Would you like to play a game to cheer up?" << endl;
    UserInput userInput;
    userInput.setResponse(username);
    string response = userInput.getResponse();
    bool userAgreed = false; // Initialize a flag to track if the user agreed to play a game

    for (string happyResponse : happyResponses) {
      if (response.find(happyResponse) != string::npos) {
        userAgreed = true;
        cout << CHATNAME << ":  " << "I'm happy to hear that " << username << endl;
        cout << CHATNAME << ":  " << "Here is the game I've been programmed to know" << endl;
        cout << "[1] Quiz" << endl;
        return userAgreed; // Return true indicating the user agreed to play a game
      }
    }

    if(!userAgreed){
      cout << CHATNAME << ":  " << "I'm sad that you don't want to play but I understand :c" << endl;
    }
    return userAgreed; // Return false indicating the user did not agree to play a game
  }

  void menuChooseValidation(const string& username){
    UserInput userInput;
    userInput.setResponse(username);
    string response = userInput.getResponse();
    int incorrectInput = 0;

    // Continue looping until the user selects option 1
    while (response != "1"){
      endConversation(response, username);
      incorrectInput++;

      // Provide feedback based on how many times the user input the incorrect input
      if (incorrectInput == 1) {
        cout << CHATNAME << ":  " << "Please be kind and input 1 to select the game" << endl;
      }
      else if (incorrectInput == 2) {
        cout << CHATNAME << ":  " << "Okay this isn't funny just press number 1 and press enter" << endl;
      }
      else { // If the user repeatedly provides incorrect inputs, display a final message and exit the program
        cout << CHATNAME << ":  " << "Wow you think you're so funny! Just get out of here we could have"
            << "played but you decided to ruin it" << endl;
        cout << "???" << ":  " << "You have angered the bot too much and thus he shut down which is supposed"
            << "to happen so just restart him" << endl;
        exit(0);
      }

      // Check if the user has selected option 1
      if (response == "1"){
        break; // Break out of the loop if the user selects option 1
      }
      userInput.setResponse(username);
      response = userInput.getResponse();
    }
  }

  // Determine the user's mood based on their response
  bool howUserIsFeeling(string& response, const string& username) const {
    while(true){
      for (string negativeWord : negativeWords) {
        if (response.find(negativeWord) != string::npos) {
          return false; // User is not feeling good
        }
      }

      for (string positiveWord : positiveWords) {
        if (response.find(positiveWord) != string::npos) {
          return true; // User is feeling good
        }
      }

      // If the response is not empty, prompt the user to clarify
      if(!response.empty()){
        cout << CHATNAME << ":  " << "Sorry, I don't understand. Could you say how it was did it go well or not that well?"
        << endl;
      }

      UserInput userInput;
      userInput.setResponse(username);
      response = userInput.getResponse();
      endConversation(response, username);
    }
  }

bool askIfUserHasHobbies(const string& username) {
    cout << CHATNAME << ":  " << "I'm happy to hear that :)" << endl;
    cout << CHATNAME << ":  " << "Is there an interesting hobby you have perhaps? (yes/no)" << endl;

    UserInput userInput;
    userInput.setResponse(username);
    string response = userInput.getResponse();
    endConversation(response, username);

    return validateYesOrNoResponse(response, username); // Return true if user has hobby, false otherwise
}

  void guessHobby(const string& username) {
    for (int i = 0; i < hobbies.size(); ++i) {
      cout << CHATNAME << ":  " << "Does your hobby happen to be " << hobbies[i] << " yes/no" << endl;
      UserInput userInput;
      userInput.setResponse(username);
      string response = userInput.getResponse();
      endConversation(response, username);

      // If the user confirms having the hobby, display information about it
      if (validateYesOrNoResponse(response, username)) {
        cout << CHATNAME << ":  " << "Your hobby is " << hobbies[i] << ". I'm glad I managed to guess it correctly." << endl;
        cout << CHATNAME << ":  " << "Fun fact about " << hobbies[i] << ":  " << funFacts[i] << endl;
        break; // Exit the loop since the hobby has been guessed
      }

      // Check if the loop has reached the last element of the hobbies vector and if the answer was no display the message
      if (i == hobbies.size() - 1) {
        cout << CHATNAME << ":  " << "I'm sorry with my limited knowledge I couldn't guess your hobby shame on me!" << endl;
      }
    }
  }

  bool validateYesOrNoResponse(string response, const string& username) {
    while (true) {
      if (response.empty()){
        //There is an error message for empty responses no additional message is neseccarry
      }
      else if (response != "yes" && response != "no") {
        cout << CHATNAME << ":  " << "Please type either yes or no" << endl;
      }
      else {
        return response == "yes"; // Return true if response is yes, false otherwise
      }

      UserInput userInput;
      userInput.setResponse(username);
      response = userInput.getResponse();
      endConversation(response, username);
    }
  }

  // Trivia game with the user using vectors of questions and their answers that are passed
  void trivia(const string& username, const vector<string>& questions, const vector<string>& answers) {
    // Loop through each question
    for (int i = 0; i < questions.size(); ++i) {
      cout << CHATNAME << ":  " << "True or false: " << questions[i] << endl;
      UserInput userInput;
      userInput.setResponse(username);
      string response = userInput.getResponse();
      endConversation(response, username);

      // Ensure the user's response is either "true" or "false"
      while (response != "true" && response != "false") {
        cout << CHATNAME << ":  " << "Please type either true or false" << endl;
        userInput.setResponse(username);
        response = userInput.getResponse();
        endConversation(response, username);
      }

      // Check if the user's response matches the correct answer
      if (response == answers[i]) {
        cout << CHATNAME << ":  " << "Correct! Good job ^^" << endl;
        triviaScore++;
      } else {
          cout << CHATNAME << ":  " << "Incorrect!" << endl;
      }
    }
  }

  // Prompt the user to play math quiz if they don't have any hobbies as a punishment
  void playMath(string username, const vector<string>& questions, const vector<string>& answers ){
    botHappiness--;
    cout << CHATNAME << ":  " << "Liar everybody has at least 1 hobby :c" << endl;
    cout << CHATNAME << ":  " << "As a punishment I will make you solve math equations and judge your skills" << endl;

    for (int i = 0; i < questions.size(); ++i) {
      cout << CHATNAME << ":  " << "What is: " << questions[i] << endl;
      UserInput userInput;
      userInput.setResponse(username);
      string response = userInput.getResponse();
      endConversation(response, username);

      if (!containsOnlyDigits(response)) {
        --i; //i decreases so the same question is asked until the user provides an answer with digits only
      }
      else{
        // Check if the user's response matches the correct answer
        if (response == answers[i]) {
          cout << CHATNAME << ":  " << "Correct!" << endl;
          mathScore++;
        }
        else {
          // Provide feedback based on the question difficulty
          switch(i){
          case 0:
            cout << CHATNAME << ":  " << "Incorrect! Really failing on the easiest question?" << endl;
            break;
          case 1:
          case 2:
            cout << CHATNAME << ":  " << "Incorrect! I guess multiplying isn't your strong point" << endl;
            break;
          default:
            cout << CHATNAME << ":  " << "Incorrect! This is a little tricky" << endl;
            break;
          }
        }
      }
    }
  }

  bool containsOnlyDigits(const string& response) {
    try {
      // Iterate through each character in the response
      for (char c : response) {
        // Check if the character is not a digit
        if (!isdigit(c)) {
          throw invalid_argument(MSG_CONTAINS_NON_DIGIT);
        }
      }
    return true; // If all characters are digits, return true
    }
    catch(const invalid_argument& e) {
      cout << "Error: " << e.what() << endl;
      return false;
    }
  }

  void endConversation(const string& response, const string& username) const {
    if (response.find("bye") != string::npos) {
      // Respond differently based on the current bot's happiness level
      switch (botHappiness) {
        case HAPPY_EXIT_HIGH:
        case HAPPY_EXIT_LOW:
          cout << CHATNAME << ":  " << "Goodbye " << username << "! Have a great day!" << endl;
          exit(0);
        case NEUTRAL_EXIT:
          cout << CHATNAME << ":  " << "Bye " << username << "! I hope you have an okay day." << endl;
          exit(0);
        default:
          cout << CHATNAME << ":  " << "Bye " << username << ". Finally I can have peace and quiet." << endl;
          exit(0);
      }
    }
  }
};

int main() {
  cout << "\t\t  Chatbot v3\n" << endl;

  // Create a User object and prompt the user to set their username
  User user;
  user.setUsername();

  ChatBot chatBot;
  chatBot.startChatBot(user.getUsername()); // Start the chatbot and greet the user

  while (true) {
    // Ask the user about their day and store their response
    bool userFeelings = chatBot.askAboutUserDay(user.getUsername());

    // If the user had a good day, ask about hobbies; otherwise, play trivia
    if(userFeelings){
      chatBot.askAboutHobbies(user.getUsername());
    }
    else{
      chatBot.playTrivia(user.getUsername());
    }

    // Prompt the user to restart or exit the conversation
    chatBot.promptRestartOrExit(user.getUsername());
  }
  return 0;
}
