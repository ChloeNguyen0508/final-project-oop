#include "Customer.h"
#include <iostream>
using namespace std;

Customer::Customer(string uname, string pass, string fname, string ph, string addr, string em, bool social)
    : User(uname, pass, fname, ph, addr, em, social) {}

string Customer::getRole() const {
    return "customer";
}

void Customer::customerMenu() {
    int choice;
    do {
        cout << "\n=== CUSTOMER MENU ===\n";
        cout << "1. Create Order\n";
        cout << "2. View Order History\n";
        cout << "3. Write Review\n";
        cout << "4. Track Order Status\n";
        cout << "5. Request Return\n";
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
