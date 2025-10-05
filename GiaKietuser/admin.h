#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"

class Admin : public User {
public:
    Admin(string uname, string pass, string fname, string ph, string addr, string em, bool social);
    string getRole() const override;
    void adminMenu();
};

#endif
