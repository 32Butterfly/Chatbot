#ifndef USER_H
#define USER_H

#include <string>

class User {
  private:
    std::string username;
  public:
    User();
    void setUsername();
    std::string getUsername() const;
};

#endif // USER_H
