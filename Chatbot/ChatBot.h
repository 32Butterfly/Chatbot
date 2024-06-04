#ifndef CHATBOT_H
#define CHATBOT_H

#include <string>
#include <vector>
#define CHATNAME "Chippie"

//Values which determine bots exit message
const int HAPPY_EXIT_HIGH = 5;
const int HAPPY_EXIT_LOW = 4;
const int NEUTRAL_EXIT = 3;

class ChatBot {
private:
  std::vector<std::string> greetings = {"Hello", "Hi", "Hey", "Greetings"};
  std::vector<std::string> negativeWords = {"bad", "not good", "terrible", "awful", "horrible", "not the best", "disappointing"};
  std::vector<std::string> positiveWords = {"good", "decent", "okay", "amazing", "really good", "splendid", "nice"};
  std::vector<std::string> hobbies = {"music", "sports", "gaming", "hiking", "reading"};
  std::vector<std::string> funFacts = {
    "Listening to music can improve mood and reduce stress levels.",
    "Regular participation in sports improves cardiovascular health and overall fitness.",
    "Gaming can improve problem-solving skills and enhance cognitive abilities.",
    "Hiking in nature can reduce negative thoughts and improve mental well-being.",
    "Reading can improve empathy and reduce the risk of cognitive decline."};
  std::vector<std::string> starterTriviaQuestions ={
    "There are 8 planets in our solar system",
    "An ant can't lift more than 3,000 times its body weight",
    "C++ was originally Called The New C"};
  std::vector<std::string> starterTriviaAnswers = { "true", "false", "true"};
  std::vector<std::string> harderTriviaQuestions= {
    "Blue eyes are newer to the human race than pottery",
    "Trees existed before sharks",
    "Matches were invented before lighters"};
  std::vector<std::string> harderTriviaAnswers = { "true", "false", "true"};
  std::vector<std::string> easierTriviaQuestions = {
    "Mount Everest is the tallest mountain in the world",
    "Vatican City is the smallest country in the world",
    "An octopus has seven hearts"};
  std::vector<std::string> easierTriviaAnswers = {"false", "true", "false"};
  std::vector<std::string> mathQuestions = {
    "20 + 5", "8 * 8", "32 * 47", "3 * (5 + 4)^2 - 100",
    "(8 * 4) + (67 + 98) - (3^2 * 2)"};
  std::vector<std::string> mathAnswers = {"25", "64", "1504", "143", "179"};
  int botHappiness = HAPPY_EXIT_HIGH;
  int triviaScore = 0;
  int mathScore = 0;
  void greetUser(const std::string& username) const;
  bool howUserIsFeeling(std::string& response, const std::string& username) const;
  bool askIfUserHasHobbies(const std::string& username);
  void guessHobby(const std::string& username);
  void trivia(const std::string& username, const std::vector<std::string>& questions, const std::vector<std::string>& answers);
  bool validateYesOrNoResponse(std::string response, const std::string& username);
  bool gameMenu(const std::string& username);
  void menuChooseValidation(const std::string& username);
  void endConversation(const std::string& response, const std::string& username) const;
  void playMath(const std::string& username, const std::vector<std::string>& questions, const std::vector<std::string>& answers);
  bool containsOnlyDigits(std::string& response);
  void failedMenuChoice(int inccorectInput);
  void triviaFeedback();
  void mathIncorrectGuessFeedback(int index);
  void mathScoreFeedback();

public:
  ChatBot();
  void startChatBot(const std::string& username);
  bool askAboutUserDay(const std::string& username);
  void playTrivia(const std::string& username);
  void askAboutHobbies(const std::string& username);
  void promptRestartOrExit(const std::string& username);
};

#endif // CHATBOT_H
