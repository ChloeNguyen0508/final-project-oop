#include "Admin.h"
#include <iostream>
using namespace std;

Admin::Admin(string uname, string pass, string fname, string ph, string addr, string em, bool social)
    : User(uname, pass, fname, ph, addr, em, social) {}

string Admin::getRole() const {
    return "admin";
}

void Admin::adminMenu() {
    int choice;
    do {
        cout << "\n=== ADMIN MENU ===\n";
        cout << "1. Add Product\n";
        cout << "2. Remove Product\n";
        cout << "3. Update Product\n";
        cout << "4. Confirm Order\n";
        cout << "5. Track Orders\n";
        cout << "6. Update Profile\n";
        cout << "7. Change Password\n";
        cout << "8. View Profile\n";
        cout << "0. Logout\n";
        cout << "Select: ";
        cin >> choice;
        switch (choice) {
            case 6: updateProfile(); break;
            case 7: changePassword(); break;
            case 8: showProfile(); break;
            case 0: cout << "Logging out...\n"; break;
            default: cout << "Function not implemented yet.\n";
        }
    } while (choice != 0);
}
