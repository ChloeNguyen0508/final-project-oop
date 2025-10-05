#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "User.h"

class Customer : public User {
public:
    Customer(string uname, string pass, string fname, string ph, string addr, string em, bool social);
    string getRole() const override;
    void customerMenu();
};

#endif
