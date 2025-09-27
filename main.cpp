#include "classes.h"
#include <fstream>
#include <sstream>

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");
    if (!in.is_open() || !out.is_open()) {
        cerr << "Không mở được file input/output!" << endl;
        return 1;
    }

    Admin admin("AdminShop", "AD001", "admin@mail.com", "0988888888", "Hanoi", "admin123", "AD001", "Manager");
    Inventory inventory;
    vector<Products> productList;
    Customers* customer = nullptr;
    Cart* cart = nullptr;

    string command;
    while (getline(in, command)) {
        if (command.empty() || command[0] == '#') continue;

        stringstream ss(command);
        string action;
        ss >> action;

        if (action == "addProduct") {
            string id, name;
            double price;
            ss >> id >> name >> price;
            Products p(id, name, price);
            productList.push_back(p);
            inventory.addStock(id, 10);
            out << "Admin da them san pham: " << name << " gia " << price << endl;
        }
        else if (action == "registerUser") {
            string name, id, mail, ph, addr, pass;
            ss >> name >> id >> mail >> ph >> addr >> pass;
            customer = new Customers(name, id, mail, ph, addr, pass, "0");
            out << "Dang ky thanh cong cho user: " << name << endl;
        }
        else if (action == "login") {
            string mail, pass;
            ss >> mail >> pass;
            if (customer && customer->login(mail, pass)) {
                cart = new Cart("C001", customer->getUserID());
                out << "Login thanh cong cho: " << customer->getUserName() << endl;
            } else {
                out << "Login that bai!" << endl;
            }
        }
        else if (action == "addToCart") {
            string pid; int qty;
            ss >> pid >> qty;
            auto it = find_if(productList.begin(), productList.end(), [&](const Products& p) {
                return p.getProductID() == pid;
            });
            if (it != productList.end() && cart) {
                CartItem item(pid, qty, it->getPrice());
                cart->addItem(item);
                out << "Them vao gio: " << it->getProductName() << " x" << qty << endl;
            }
        }
        else if (action == "checkout") {
            if (cart) {
                out << "------ Hoa don ------" << endl;
                cart->displayCart();
                out << "Tong tien phai tra: " << cart->getTotalAmount() << endl;
            }
        }
    }

    in.close();
    out.close();
    return 0;
}
