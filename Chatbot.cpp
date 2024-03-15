#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

#define CHATNAME "Chippie"
const int HAPPY_EXIT_HIGH = 5;
const int HAPPY_EXIT_LOW = 4;
const int NEUTRAL_EXIT = 3;

string toLowercase(string response) {
  for (char &c : response) {
    c = tolower(c);
  }
  return response;
}

void endConversation(string response, string username, int botHappiness) {
  if (toLowercase(response).find("bye") != string::npos) {
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

string getUserInput(string username) {
  string response;
  cout << username << ":  ";
  getline(cin, response);

  if (response.empty()) {
    cout << CHATNAME << ":  " << "Please enter a valid input" << endl;
    return getUserInput(username);
  }

  if(response.length() >= 30){
    cout << CHATNAME <<":  " << "The input is too long. Are you trying to break me perhaps?" << endl;
    return getUserInput(username);
  }

  response = toLowercase(response);

  return response;
}

int playTrivia(string question, string answer, int& score, string username, int botHappiness) {
  string response;
  cout << CHATNAME << ":  " << "True or false: " << question << endl;
  cout << username << ":  ";
  getline(cin, response);

  response = toLowercase(response);
  endConversation(response, username, botHappiness);

  while (response != "true" && response != "false") {
  cout << CHATNAME << ":  " << "Please type either true or false" << endl;
  response = getUserInput(username);
  endConversation(response, username, botHappiness);
  }

  if (response.find(toLowercase(answer)) != string::npos) {
    cout << CHATNAME << ":  " << "Correct! Good job ^^" << endl;
    score++;
  }
  else {
    cout << CHATNAME << ":  " << "Incorrect!" << endl;
  }
  return score;
}

bool isValidUsername(const string& username) {
  return (username.length() >= 3 && username.length() <= 20);
}

bool askAboutDay(string username, int botHappiness) {
  cout << CHATNAME << ":  " << "Hello " << username << " how was your day so far? (good/bad)" << endl;
  string response = getUserInput(username);
  endConversation(response, username, botHappiness);
  bool isNegative = false;
  bool isPositive = false;

  while (!isNegative && !isPositive) {
    vector<string> negativeWords = {"bad", "not good", "terrible", "awful", "horrible", "not the best", "disappointing"};
      for (string negativeWord : negativeWords) {
        if (response.find(negativeWord) != string::npos) {
          isNegative = true;
          break;
        }
      }

    vector<string> positiveWords = {"good", "decent", "okay", "amazing", "really good", "splendid", "nice"};
      for (string positiveWord : positiveWords) {
        if (response.find(positiveWord) != string::npos) {
          isPositive = true;
            break;
        }
      }

    if (!isNegative && !isPositive) {
      cout << CHATNAME << ":  " << "Sorry, I don't understand. Could you say how it was did it go well or not that well?" << endl;
      response = getUserInput(username);
      endConversation(response, username, botHappiness);
    }
  }
  return isNegative;
}

int main() {
  srand(static_cast<unsigned int>(time(0)));

  string username;
  vector<string> greetings = {"Hello", "Hi", "Hey", "Greetings"};
  int greetIndex = rand() % greetings.size();

  cout << "\t\tChatbot v2\n";
  cout << "\n" << CHATNAME << ":  " << greetings[greetIndex] << " my name is " << CHATNAME << " what is your name?\n";
  cout << "User:  ";
  getline(cin, username);

  while (!isValidUsername(username)) {
    cout << CHATNAME << ": " << "Please enter a username with length between 3 and 20 characters " <<endl;
    cout << "User: ";
    getline(cin, username);
  }
  if (toLowercase(username).find("bye") != string::npos){
    cout << CHATNAME << ":  " << "Goodbye Unknown!" << endl;
    exit(0);
  }

  cout << CHATNAME << ":  " << "Quick reminder you can type bye/goodbye to exit the program" << endl;

  while (true) {
    int botHappiness = 5;
    cin.clear();
    string response;
    bool isNegative = askAboutDay(username, botHappiness);

    if (isNegative == true) {
      cout << CHATNAME << ":  " << "I'm sorry to hear that. Would you like to play a game to cheer up?" << endl;
      response = getUserInput(username);
      endConversation(response, username, botHappiness);

      vector<string> happyResponses = {"yes", "sure", "okay", "why not", "of course", "yea", "ofcourse"};
      bool userAgreed = false;
        for (string happyResponse : happyResponses) {
          if (response.find(happyResponse) != string::npos) {
            userAgreed = true;
            cout << CHATNAME << ":  " << "I'm happy to hear that " << username << endl;
            cout << CHATNAME << ":  " << "Here is the game I've been programmed to know" << endl;
            cout << "[1] Quiz" << endl;
            cout << "More coming soon maybe?" << endl;
            response = getUserInput(username);

            while (response != "1") {
              response = toLowercase(response);
              endConversation(response, username, botHappiness);

              botHappiness--;
                if (botHappiness > 3) {
                  cout << CHATNAME << ":  " << "Please be kind and input 1 to select the game" << endl;
                }
                else if (botHappiness > 2) {
                    cout << CHATNAME << ":  " << "Okay this isn't funny just press number 1 and press enter" << endl;
                }
                else {
                  cout << CHATNAME << ":  " << "Wow you think you're so funny! Just get out of here we could have"
                  << "played but you decided to ruin it" << endl;
                  cout << "???" << ":  " << "You have angered the bot too much and thus he shut down which is supposed"
                  << "to happen so just restart him" << endl;
                  return 0;
                }

                if (response == "1"){
                  break;
                }
                cin.clear();
                response = getUserInput(username);
              }
              int score = 0;
              score = playTrivia("There are 8 planets in our solar system", "true", score, username, botHappiness);
              score = playTrivia("An ant can't lift more than 3,000 times its body weight", "false", score, username, botHappiness);
              score = playTrivia("C++ was originally Called The New C", "true", score, username, botHappiness);

              if (score >= 2) {
                cout << CHATNAME << ":  " << "You are doing fairly well so the questions will become a little harder ^^" << endl;
                score = playTrivia("Blue eyes are newer to the human race than pottery", "false", score, username, botHappiness);
                score = playTrivia("Trees existed before sharks", "false", score, username, botHappiness);
                score = playTrivia("Matches were invented before lighters", "false", score, username, botHappiness);

                if (score == 6) {
                  cout << CHATNAME << ":  " << "You've got all of the right congratulations!" << endl;
                }
                else if (score < 6 && score > 3) {
                  cout << CHATNAME << ":  " << "You answered " << score << "/6 questions which is not bad ^^" << endl;
                }
                else {
                  cout << CHATNAME << ":  " << "You answered " << score << "/6 questions which is not the best but you did well nonetheless" << endl;
                }
                cout << CHATNAME << ":  " << "The game has ended!" << endl;
              }
              else {
                botHappiness--;
                cout << CHATNAME << ":  " << "You're not doing too well so we won't delve into the harder questions!" << endl;
                score = playTrivia("Mount Everest is the tallest mountain in the world", "false", score, username, botHappiness);
                score = playTrivia("Vatican City is the smallest country in the world", "true", score, username, botHappiness);
                score = playTrivia("An octopus has seven hearts", "false", score, username, botHappiness);

                if (score > 2) {
                  cout << CHATNAME << ":  " << "You answered " << score << "/6 questions which is not bad ^^" << endl;
                }
                else {
                  botHappiness--;
                  cout << CHATNAME << ":  " << "Pretty disappointing you only managed to answer " << score << "/6" << endl;
                }
                cout << CHATNAME << ":  " << "The game has ended!" << endl;
              }
            break;
          }
        }
        if (!userAgreed){
          cout << CHATNAME << ":  " << "I'm sad that you don't want to play but I understand :c" << endl;
        }
      }
    else {
      cout << CHATNAME << ":  " << "I'm happy to hear that :)" << endl;
      cout << CHATNAME << ":  " << "Is there an interesting hobby you have perhaps? (yes/no)" << endl;
      response = getUserInput(username);
      endConversation(response, username, botHappiness);

      while (response != "yes" && response != "no"){
        cout << CHATNAME << ":  " << "Please select (yes/no)" << endl;
        response = getUserInput(username);
        endConversation(response, username, botHappiness);
      }

      if(response.find("yes") != string::npos){
        vector<string> hobbies = {"music", "sports", "gaming", "hiking", "reading"};
        vector<string> funFacts = {
          "Listening to music can improve mood and reduce stress levels.",
          "Regular participation in sports improves cardiovascular health and overall fitness.",
          "Gaming can improve problem-solving skills and enhance cognitive abilities.",
          "Hiking in nature can reduce negative thoughts and improve mental well-being.",
          "Reading can improve empathy and reduce the risk of cognitive decline."};

        for (int i = 0; i < hobbies.size(); ++i){
          cout << CHATNAME << ":  " << "Does your hobby happen to be " << hobbies[i] << " yes/no" <<endl;
          response = getUserInput(username);
          endConversation(response, username, botHappiness);

          while (response != "yes" && response != "no"){
            botHappiness--;
            cout << CHATNAME << ":  " << "Please select yes or no" <<endl;
            response = getUserInput(username);
            endConversation(response, username, botHappiness);
          }
          if (response.find("no") != string::npos){
            if(hobbies.size() - i == 1){
              cout << CHATNAME << ":  " << "I'm sorry with my limited knowledge I couldn't guess your hobby shame on me!" << endl;
            }
          continue;
          }
        else{
          cout << CHATNAME << ":  " << "Your hobby is " <<hobbies[i] << ". I'm glad I managed to guess it correctly." << endl;
          cout << CHATNAME << ":  " << "Fun fact about " <<hobbies[i] << ":  " << funFacts[i] << endl;
          break;
        }
      }
    }
      else{
        cout << CHATNAME << ":  " << "It's not like I could share your secrets anyway :c" << endl;
        botHappiness-=2;
      }
    }
    cout << CHATNAME << ":  " << "Would you like to start over the conversation or exit?" << endl;
    response = getUserInput(username);
    endConversation(response, username, botHappiness);

    while(response.find("exit") == string::npos && response.find("start over") == string::npos){
    cout << CHATNAME << ":  " << "Please type either exit or start over" << endl;
    response = getUserInput(username);
    endConversation(response, username, botHappiness);
    }
    if (response.find("exit") != string::npos){
      endConversation("bye", username, botHappiness);
    }
    else{
      continue;
    }
  }
  return 0;
}
