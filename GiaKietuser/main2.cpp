#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "Admin.h"
#include "Customer.h"
using namespace std;

vector<User*> loadUsers(const string &filename) {
    ifstream in(filename);
    vector<User*> users;
    int n; in >> n;
    for (int i = 0; i < n; i++) {
        string type, uname, pass, fname, ph, addr, em;
        bool social;
        in >> type >> uname >> pass >> fname >> ph >> addr >> em >> social;
        for (auto &c : fname) if (c == '_') c = ' ';
        if (type == "admin")
            users.push_back(new Admin(uname, pass, fname, ph, addr, em, social));
        else
            users.push_back(new Customer(uname, pass, fname, ph, addr, em, social));
    }
    return users;
}

void saveUsers(const vector<User*> &users, const string &filename) {
    ofstream out(filename);
    out << users.size() << "\n";
    for (auto u : users) out << u->serialize() << "\n";
}

int main() {
    vector<User*> users = loadUsers("input.txt");

    string uname, pass;
    cout << "=== LOGIN ===\n";
    cout << "Username: ";
    cin >> uname;
    cout << "Password: ";
    cin >> pass;

    User* loggedInUser = nullptr;
    for (auto u : users) {
        if (u->login(uname, pass)) {
            loggedInUser = u;
            break;
        }
    }

    if (!loggedInUser) {
        cout << "Invalid username or password.\n";
    } else {
        if (loggedInUser->getRole() == "admin")
            ((Admin*)loggedInUser)->adminMenu();
        else
            ((Customer*)loggedInUser)->customerMenu();
    }

    saveUsers(users, "output.txt");
    for (auto u : users) delete u;
    return 0;
}
