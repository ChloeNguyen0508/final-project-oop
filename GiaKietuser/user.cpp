#include "User.h"
#include <iostream>
#include <sstream>
using namespace std;

User::User(string uname, string pass, string fname, string ph, string addr, string em, bool social)
    : username(uname), password(pass), fullName(fname), phone(ph), address(addr), email(em), socialLogin(social) {}

User::~User() {}

string User::getUsername() const { return username; }
string User::getPassword() const { return password; }
string User::getRole() const { return "user"; }

bool User::login(const string& u, const string& p) {
    if (u == username && p == password) {
        cout << "Login successful: " << username << "\n";
        return true;
    }
    return false;
}

void User::updateProfile() {
    cout << "Enter new full name (use _ for space): ";
    string fname; cin >> fname;
    for (auto &c : fname) if (c == '_') c = ' ';
    fullName = fname;

    cout << "Enter new phone: ";
    cin >> phone;
    cout << "Enter new email: ";
    cin >> email;
    cout << "Enter new address: ";
    cin >> address;
    cout << "Profile updated successfully!\n";
}

void User::changePassword() {
    string oldp, newp;
    cout << "Enter old password: ";
    cin >> oldp;
    if (oldp != password) {
        cout << "Incorrect old password.\n";
        return;
    }
    cout << "Enter new password: ";
    cin >> newp;
    password = newp;
    cout << "Password changed successfully!\n";
}

void User::showProfile() const {
    cout << "Username: " << username << "\n";
    cout << "Full Name: " << fullName << "\n";
    cout << "Phone: " << phone << "\n";
    cout << "Email: " << email << "\n";
    cout << "Address: " << address << "\n";
}

string User::serialize() const {
    string temp = fullName;
    for (auto &c : temp) if (c == ' ') c = '_';
    ostringstream oss;
    oss << getRole() << " " << username << " " << password << " " << temp << " "
        << phone << " " << address << " " << email << " " << socialLogin;
    return oss.str();
}
