#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

string toLowercase(string str){ //convert string to all lower cases
  for (char &c : str){
      c = tolower(c);
  }
  return str;
}
// whenever you say bye/goodbye the conversation ends except when asked for username
int endConversation(string str, string chatname, string username, int state){
  if(toLowercase(str).find("bye") != string::npos){
      switch(state){
        case 5:
        case 4:
          cout << chatname << ":  " << "Goodbye " << username << "! Have a great day!" << endl;
          return 1;
        case 3:
          cout << chatname << ":  " << "Bye " << username << "! I hope you have an okay day." << endl;
          return 1;
        default:
          cout << chatname << ":  " << "Bye " << username << ". Finally I can have peace and quiet" << endl;
          return 1;
      }
  }
  return 0;
}
//game logic which check whether you put the correct answer in the game
int gameScore(string str, string Answer, int score, string chatname) {
  if(str.find(toLowercase(Answer)) != string::npos){
      cout << chatname << ":  " << "Correct! Good job ^^" << endl;
      score++;
  }
  else {
      cout << chatname << ":  " << "Incorrect! That wasn't that difficult" << endl;
  }
  return score;
}
//this function saves me from having to write the same thing over and over again to get user input :)
string getUserInput(string username) {
    string response;
    cout << username << ":  ";
    getline(cin, response);
    response = toLowercase(response);
    return response;
}

int main() {
  srand(static_cast<unsigned int>(time(0)));

  string username, chatname = "Chippie";
  int score = 0; //game score how many you answered correctly
  vector<string> greetings = {"Hello", "Hi", "Hey", "Greetings"}, happyResponses = {"yes", "sure", "okay", "why not", "ofcourse", "yea"};

  int greetIndex = rand() % greetings.size();

  cout << "\t\tChatbot v1\n";
  cout << "\n" << chatname << ":  " << greetings[greetIndex] << " my name is " << chatname << " what is your name?\n";
  cout << "User:  ";
  getline(cin, username);
  cout <<chatname << ":  " <<"Quick reminder you can type bye/goodbye to exit the program"<<endl;

  while (true) {
    int botHappiness = 5; // 4 or above - happy; 3- annoyed; 2 or below - angry also reset every loop
    cin.clear(); //this clears the user input when the loop starts over
    cout << chatname << ":  "<< "Hello " << username << " how was your day so far?" << endl;
    string response;
    response = getUserInput(username);

    if (endConversation(response, chatname, username, botHappiness)) break;

    response = toLowercase(response);

    if (response.find("bad") != string::npos) { //you have to put in bad to get this route
      cout << chatname << ":  " <<"I'm sorry to hear that. Would you like to play a game to cheer up?" << endl;
      response = getUserInput(username);

        for (string happyResponse : happyResponses) { //go through all of the happyResponses to see whether the user agrees to play the game
            if (response.find(happyResponse) != string::npos) {
                cout << chatname << ":  " <<"I'm happy to hear that " << username << endl;
                cout << chatname << ":  " <<"Here is the game I've been programmed to know" << endl;
                cout << "[1] Quiz" << endl;
                cout << "More coming soon maybe?" <<endl;
                response = getUserInput(username);

                while (response != "1") { //this loop is for making sure the user inputs 1 if they fail 3 times the bot gets angry and "shuts down"
                    response = toLowercase(response);
                    if (endConversation(response, chatname, username, botHappiness)) return 0;

                    botHappiness--;
                    if (botHappiness > 3) {
                        cout << chatname << ":  " << "Please be kind and input 1 to select the game" << endl;
                    }
                    else if (botHappiness > 2) {
                        cout << chatname << ":  " << "Okay this isn't funny just press number 1 and press enter" << endl;
                    }
                    else {
                        cout << chatname << ":  " << "Wow you think you're so funny! Just get out of here we could have played but you decided to ruin it" << endl;
                        cout << "???" << ":  " << "You have angered the bot too much and thus he shut down which is supposed to happen so just restart him" << endl;
                        return 0;
                    }

                    if (response == "1") break;

                    cin.clear();
                    response = getUserInput(username);
                }
                  //the game begins
                  cout << chatname << ":  " << "True or false: There are 8 planets in our solar system" << endl;
                  response = getUserInput(username);
                  if (endConversation(response, chatname, username, botHappiness)) return 0;
                  score = gameScore(response, "true", score, chatname);

                  cout << chatname << ":  " << "True or false: An ant can't lift more than 3,000 times its body weight" << endl;
                  response = getUserInput(username);
                  if (endConversation(response, chatname, username, botHappiness)) return 0;
                  score = gameScore(response, "false", score, chatname);

                  cout << chatname << ":  " << "True or false: C++ was originally Called The New C" << endl;
                  response = getUserInput(username);
                  if (endConversation(response, chatname, username, botHappiness)) return 0;
                  score = gameScore(response, "true", score, chatname);

                  if (score >= 2){ //if you get 2 or 3 right you get harder questions
                    cout << chatname << ":  " <<"You are doing fairly well so the questions will become a little harder ^^" <<endl;
                    cout << chatname<< ":  "  <<"True or false Blue eyes are newer to the human race than pottery?" <<endl;
                    response = getUserInput(username);
                    if (endConversation(response, chatname, username, botHappiness)) return 0;
                    score = gameScore(response, "false", score, chatname);

                    cout << chatname <<": " <<"True or false Trees existed before sharks. " <<endl;
                    response = getUserInput(username);
                    if (endConversation(response, chatname, username, botHappiness)) return 0;
                    score = gameScore(response, "false", score, chatname);

                    cout << chatname <<": " <<" True or false Matches were invented before lighters." <<endl;
                    response = getUserInput(username);
                    if (endConversation(response, chatname, username, botHappiness)) return 0;
                    score = gameScore(response, "false", score, chatname);

                    if (score == 6){
                      cout<< chatname <<": " <<"You've got all of the right congratulations!"<<endl;
                      cout<< chatname <<": " <<"The game has ended!"<<endl;
                    }
                    else if (score < 6 && score > 3){
                      cout << chatname <<": " <<"You answered " <<score <<"/6 questions which is not bad ^^" <<endl;
                      cout<< chatname <<": " <<"The game has ended!"<<endl;
                    }
                    else{
                      cout << chatname <<": " <<"You answered " <<score <<"/6 questions which is not the best but you did well non the less" <<endl;
                      cout<< chatname <<": " <<"The game has ended!"<<endl;
                    }
                  }
                  else{ //if you only managed to answer 1 or 0 correctly then you stay with the easier questions
                      botHappiness--;
                      cout << chatname <<": " <<"You're doing not to well so we won't delve into the harder questions!" <<endl;
                      cout << chatname <<": " <<"True or false Mount Everest is the tallest mountain in the world?" <<endl;
                      response = getUserInput(username);
                      if (endConversation(response, chatname, username, botHappiness)) return 0;
                      score = gameScore(response, "false", score, chatname);

                      cout << chatname <<": " <<"True or false Vatican City is the smallest country in the world?" <<endl;
                      response = getUserInput(username);
                      if (endConversation(response, chatname, username, botHappiness)) return 0;
                      score = gameScore(response, "true", score, chatname);

                      cout << chatname <<": " <<"True or false An octopus has seven hearts?" <<endl;
                      response = getUserInput(username);
                      if (endConversation(response, chatname, username, botHappiness)) return 0;
                      score = gameScore(response, "false", score, chatname);
                      if(score > 2){
                        cout << chatname <<": " <<"You answered " <<score <<"/6 questions which is not bad ^^" <<endl;
                      }
                      else {
                          botHappiness--;
                        cout << chatname <<": " <<"Pretty dissapointing you only managed to answer " <<score <<"/6" <<endl;
                      }
                      cout<< chatname <<": " <<"The game has ended!"<<endl;
                    }
                  break;
              }
          }
      }
      else { //this is the route if you say you had a good day
        cout << chatname << ":  " << "I'm happy to hear that :)" << endl;
        cout << chatname << ":  " << "Is there an interesting hobby you have perhaps?" << endl;
        response = getUserInput(username);
        if (endConversation(response, chatname, username, botHappiness)) break;

    if (response.find("no")== string::npos ) {
        cout << chatname << ":  " << "That's wonderful! " << response << " sounds intriguing. What specifically draws you to this interest?" << endl;
        response = getUserInput(username);
        if (endConversation(response, chatname, username, botHappiness)) break;

        cout << chatname << ":  " << "I see, " << response << ". That's really interesting! It's great to hear your perspective on it." << endl;
        cout << chatname << ":  " << "By the way, have you discovered anything surprising or unexpected related to " << response << "? yes/no" << endl;
        response = getUserInput(username);

        if (endConversation(response, chatname, username, botHappiness)) break;

        if (response.find("yes") != string::npos) {
            cout << chatname << ":  " << "That's fascinating! I'd love to hear more about it." << endl;
        } else {
            botHappiness--;
            cout << chatname << ":  " << "You know I'm just a chat bot so you can spill your secrets!" << endl;
        }

    } else {
      botHappiness--;
        cout << chatname << ":  " << "No worries! I understand but it's not like I'm going to share anything probably" << endl;
    }
  }
  //this is promted each time when you complete a route and lets you choose whether to continue or exit
  cout << chatname << ":  " <<"Would you like to start over the conversation or exit?" <<endl;
  response = getUserInput(username);
  if (endConversation(response, chatname, username, botHappiness)) break;

  if(response.find("exit")!= string::npos ) break;
    else continue;
  }
  return 0;
}
