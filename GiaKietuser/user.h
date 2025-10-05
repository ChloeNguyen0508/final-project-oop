#ifndef USER_H
#define USER_H

#include <string>
using namespace std;

class User {
protected:
    string username;
    string password;
    string fullName;
    string phone;
    string address;
    string email;
    bool socialLogin;

public:
    User(string uname, string pass, string fname, string ph, string addr, string em, bool social);
    virtual ~User();

    string getUsername() const;
    string getPassword() const;
    virtual string getRole() const;

    bool login(const string& u, const string& p);
    void updateProfile();
    void changePassword();
    virtual void showProfile() const;

    virtual string serialize() const;
};

#endif
