#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

// --------------------Product---------------------- uiiiaihuirwhctghiegt
class Products
{
private:
    string productID;
    string productName;
    double price;
    string description;
    vector<string> images; // Url dan toi file anh
    map<string, int> sizeStock;

public:
    Products(string id, string name, double p)
    {
        productID = id;
        productName = name;
        price = p;
        description = "";
    }
    void setProductID(string id) { productID = id; }
    void setProductName(string name) { productName = name; }
    void setPrice(double p) { price = p; }
    void setDescription(const string &d) { description = d; }
    void setSizeStock(const string &size, int qty) { sizeStock[size] = qty; }
    string getDescription() const { return description; }
    string getProductID() const { return productID; }
    string getProductName() const { return productName; }
    double getPrice() const { return price; }
    bool isAvailable() const
    {
        if (price <= 0)
            return false;
        for (const auto &k : sizeStock)
            if (k.second > 0)
                return true;
        return images.size() > 0;
    }
    double getDiscount(double percent) const
    {
        if (percent <= 0)
            return price;
        if (percent >= 100)
            return 0;
        return price * (1 - percent / 100);
    }
    void addImages(const string &url)
    {
        images.push_back(url);
    }
    void displayInfo() const
    {
        cout << "ProductID: " << productID
             << " | Name: " << productName
             << " | Price: " << price << endl;
    }
};
// --------------------Category----------------------
class Category
{
private:
    string categoryID;
    string categoryName;
    string description;
    vector<Products> products; // danh sách sản phẩm trong danh mục

public:
    Category(string id, string name, string des)
    {
        categoryID = id;
        categoryName = name;
        description = des;
    }

    void setCategoryID(string id) { categoryID = id; }
    void setCategoryName(string name) { categoryName = name; }
    void setDescription(string des) { description = des; }
    string getCategoryID() const { return categoryID; }
    string getCategoryName() const { return categoryName; }
    string getDescription() const { return description; }

    void addProduct(const Products &p)
    {
        products.push_back(p);
    }

    void listProducts()
    {
        cout << "Category: " << categoryName
             << " | Description: " << description << endl;
        if (products.empty())
        {
            cout << " No products in this category." << endl;
        }
        else
        {
            for (const auto &p : products)
            {
                p.displayInfo();
            }
        }
    }
};

//---------------------CartItem----------------------
class CartItem
{
private:
    string productID;
    int quantity; // số lượng sản phẩm
    double unitPrice;
    double totalPrice; // tổng giá tiền

public:
    CartItem(string pid, int qty, double price)
    {
        productID = pid;
        quantity = qty;
        unitPrice = price;
        totalPrice = quantity * unitPrice;
    }
    void setProductID(string pid) { productID = pid; }
    void setQuantity(int qty) { quantity = qty; }
    void setUnitPrice(double price) { unitPrice = price; }
    void setTotalPrice(double tprice) { totalPrice = tprice; }
    string getProductID() const { return productID; }
    int getQuantity() const { return quantity; }
    double getUnitPrice() const { return unitPrice; }
    double getTotalPrice() const { return totalPrice; }

    void operator+=(int newqty)
    {
        quantity += newqty;
        totalPrice = quantity * unitPrice; // Cập nhật tổng giá tiền
    }

    void operator-=(int qty)
    {
        quantity -= qty;
        if (quantity < 0)
            quantity = 0; // tránh âm
        totalPrice = quantity * unitPrice;
    }

    void displayInfo() const
    {
        cout << "ProductID: " << productID
             << " | Quantity: " << quantity
             << " | Unit Price: " << unitPrice
             << " | Total Price: " << totalPrice << endl;
    }
};

//--------------------Cart----------------------
class Cart
{
private:
    string cartID;
    string customerID;
    double totalAmount;     // tổng số tiền trong giỏ hàng
    vector<CartItem> items; // danh sách sản phẩm trong giỏ hàng

public:
    Cart(string cid, string cuid)
    {
        cartID = cid;
        customerID = cuid;
        totalAmount = 0.0;
    }
    void setCartID(string cid) { cartID = cid; }
    void setCustomerID(string cuid) { customerID = cuid; }
    void setTotalAmount(double amount) { totalAmount = amount; }
    string getCartID() const { return cartID; }
    string getCustomerID() const { return customerID; }
    double getTotalAmount() const { return totalAmount; }

    void addItem(const CartItem &item)
    {
        // Kiểm tra nếu sản phẩm đã có trong giỏ hàng
        auto it = find_if(items.begin(), items.end(), [&](const CartItem &ci)
                          { return ci.getProductID() == item.getProductID(); });
        if (it != items.end())
        {
            // Nếu có, tăng số lượng
            *it += item.getQuantity();
        }
        else
        {
            // Nếu không, thêm sản phẩm mới
            items.push_back(item);
        }
        // Cập nhật lại totalAmount chính xác bằng cách cộng lại toàn bộ items
        totalAmount = 0;
        for (const auto &ci : items)
        {
            totalAmount += ci.getTotalPrice();
        }
    }
    void removeItem(const string &pid, int qty)
    {
        auto it = find_if(items.begin(), items.end(), [&](const CartItem &ci)
                          { return ci.getProductID() == pid; });
        if (it != items.end())
        {
            *it -= qty;
            if (it->getQuantity() <= 0)
            {
                items.erase(it);
            }
            // Cập nhật lại totalAmount chính xác bằng cách cộng lại toàn bộ items
            totalAmount = 0;
            for (const auto &ci : items)
            {
                totalAmount += ci.getTotalPrice();
            }
        }
        else
        {
            cout << "Product not found in cart." << endl;
        }
    }

    void clearCart()
    {
        items.clear();
        totalAmount = 0.0;
    }

    double calculateTotal() const
    {
        double sum = 0.0;
        for (const auto &ci : items)
            sum += ci.getTotalPrice();
        return sum;
    }

    void updateQuantity(const string &pid, int qty)
    {
        auto it = find_if(items.begin(), items.end(), [&](CartItem &ci)
                          { return ci.getProductID() == pid; });
        if (it != items.end())
        {
            if (qty <= 0)
            {
                items.erase(it);
            }
            else
            {
                it->setQuantity(qty);
                it->setTotalPrice(qty * it->getUnitPrice());
            }
            totalAmount = calculateTotal();
        }
        else
        {
            cout << "Product not found in cart." << endl;
        }
    }
    bool validateMaxItems(int maxItems) const
    {
        int totalQty = 0;
        for (const auto &ci : items)
            totalQty += ci.getQuantity();
        return totalQty <= maxItems;
    }
    void displayCart() const
    {
        cout << "CartID: " << cartID
             << " | CustomerID: " << customerID
             << " | Total Amount: " << totalAmount << endl;
        if (items.empty())
        {
            cout << " Cart is empty." << endl;
        }
        else
        {
            for (const auto &item : items)
            {
                item.displayInfo();
            }
        }
    }
};
//--------------------Wishlist----------------------
class Wishlist
{
private:
    string wishlistID;
    string customerID;
    vector<string> items; // danh sách sản phẩm trong wishlist

public:
    Wishlist(string wid, string cid)
    {
        wishlistID = wid;
        customerID = cid;
    }
    void setWishlistID(string wid) { wishlistID = wid; }
    void setCustomerID(string cid) { customerID = cid; }
    string getWishlistID() const { return wishlistID; }
    string getCustomerID() const { return customerID; }

    void addItem(const string &item)
    {
        items.push_back(item);
    }

    void removeItem(const string &item)
    {
        auto it = find(items.begin(), items.end(), item);
        if (it != items.end())
        {
            items.erase(it);
        }
        else
        {
            cout << "Item not found in wishlist." << endl;
        }
    }

    void displayWishlist() const
    {
        cout << "WishlistID: " << wishlistID
             << " | CustomerID: " << customerID << endl;
        if (items.empty())
        {
            cout << " Wishlist is empty." << endl;
        }
        else
        {
            for (const auto &item : items)
            {
                cout << " - " << item << endl;
            }
        }
    }
};

// --------------------Order----------------------
class Order
{
private:
    string orderID;
    string customerID;
    string status;
    string orderDate;
    vector<string> items; // danh sách sản phẩm trong đơn hàng

public:
    Order(string oid, string cid, string sta, string odate)
    {
        orderID = oid;
        customerID = cid;
        status = sta;
        orderDate = odate;
    }

    void setOrderID(string oid) { orderID = oid; }
    void setCustomerID(string cid) { customerID = cid; }
    void setStatus(string sta) { status = sta; }
    void setOrderDate(string odate) { orderDate = odate; }
    string getOrderID() const { return orderID; }
    string getCustomerID() const { return customerID; }
    string getStatus() const { return status; }
    string getOrderDate() const { return orderDate; }

    void addItem(const string &item) { items.push_back(item); }
    void updateStatus(const string &sta)
    {
        status = sta;
        cout << "Order " << orderID << " status updated to: " << status << endl;
    }

    void cancelOrder()
    {
        if (status == "Cancelled")
        {
            cout << "Order already cancelled." << endl;
            return;
        }
        status = "Cancelled";
        cout << "Order " << orderID << " cancelled." << endl;
    }

    void confirmOrder()
    {
        if (status == "Confirmed")
        {
            cout << "Order already confirmed." << endl;
            return;
        }
        status = "Confirmed";
        cout << "Order " << orderID << " confirmed." << endl;
    }

    void processReturn()
    {
        status = "Return Processed";
        cout << "Order " << orderID << " return processed." << endl;
    }
};

// --------------------OrderManager----------------------
class OrderManager
{
private:
    vector<Order> orders;

public:
    void addOrder(const Order &ord)
    {
        orders.push_back(ord);
    }

    bool updateOrderStatus(const string &oid, const string &newStatus)
    {
        for (auto &ord : orders)
        {
            if (ord.getOrderID() == oid)
            {
                ord.updateStatus(newStatus);
                return true;
            }
        }
        return false;
    }

    string getOrderStatus(const string &oid) const
    {
        for (const auto &ord : orders)
        {
            if (ord.getOrderID() == oid)
                return ord.getStatus();
        }
        return "Order not found";
    }

    // xem lịch sử đơn hàng của khách hàng
    void viewOrderByCustomer(const string &cid)
    {
        cout << "Order of customer ID: " << cid << endl;
        for (const auto &ord : orders)
        {
            if (ord.getCustomerID() == cid)
            {
                cout << " -OrderID: " << ord.getOrderID();
                cout << "| Status: " << ord.getStatus() << endl;
            }
        }
    }

    // xem tất cả đơn hàng chỉ có Admin/Manager mới xem được
    void viewAllOrders()
    {
        cout << "All Orders: " << endl;
        for (const auto &ord : orders)
        {
            cout << " - OrderID: " << ord.getOrderID()
                 << " | CustomerID: " << ord.getCustomerID()
                 << " | Status: " << ord.getStatus() << endl;
        }
    }

    // xem đơn hàng trong một ngày cụ thể
    void viewOrdersByDate(const string &date)
    {
        cout << "Orders on " << date << ":" << endl;
        bool found = false;
        for (const auto &ord : orders)
        {
            if (ord.getOrderDate() == date)
            {
                cout << " -OrderID: " << ord.getOrderID()
                     << " | CustomerID: " << ord.getCustomerID()
                     << " | Status: " << ord.getStatus() << endl;
                found = true;
            }
        }
        if (!found)
        {
            cout << "No orders found on this date." << endl;
        }
    }
    // Thống kê số lượng đơn theo ngày
    void orderStatisticsByDate()
    {
        map<string, int> countByDate;

        for (const auto &ord : orders)
        {
            countByDate[ord.getOrderDate()]++;
        }

        cout << "Order Statistics by Date:" << endl;
        for (const auto &entry : countByDate)
        {
            cout << " - " << entry.first << ": " << entry.second << " orders" << endl;
        }
    }
};

// --------------------User----------------------
class User
{
protected:
    string userName;
    string userID;
    string email;
    string phone;
    string address;
    string password;
    bool isLoggedIn;

public:
    User(string name, string id, string mail, string ph, string addr, string pass)
    {
        userName = name;
        userID = id;
        email = mail;
        phone = ph;
        address = addr;
        password = pass;
        isLoggedIn = false;
    }

    void setUserName(string name) { userName = name; }
    void setUserID(string id) { userID = id; }
    void setEmail(string mail) { email = mail; }
    void setPhone(string ph) { phone = ph; }
    void setAddress(string addr) { address = addr; }
    void setPassword(string pass) { password = pass; }
    string getUserName() const { return userName; }
    string getUserID() const { return userID; }
    string getEmail() const { return email; }
    string getPhone() const { return phone; }
    string getAddress() const { return address; }
    string getPassword() const { return password; }

    void registerAccount(const string &newEmail, const string &newPassword)
    {
        email = newEmail;
        password = newPassword;
        cout << "Account registered successfully with email: " << email << endl;
    }

    // login
    bool login(const string &inputEmail, const string &inputPass)
    {
        if (inputEmail == email && inputPass == password)
        {
            isLoggedIn = true;
            cout << "Login successfull! Welcome " << userName << endl;
            return true;
        }
        cout << "Login failed! Invalid email or password." << endl;
        return false;
    }

    // logout
    void logout()
    {
        isLoggedIn = false;
        cout << "User " << userName << " logged out." << endl;
    }

    // updateProfile
    void updateProfile(const string &name, const string &mail)
    {
        userName = name;
        email = mail;
        cout << "Profile updated successfully." << endl;
    }

    // viewOrders
    void viewOrders()
    {
        cout << "Viewing orders for user: " << userName << endl;
        // Hiển thị danh sách đơn hàng (giả lập)
        cout << "Order 1: OrderID 001, Status: Delivered" << endl;
        cout << "Order 2: OrderID 002, Status: In Transit" << endl;
    }
};

// --------------------Customers----------------------
class Customers : public User
{

private:
    string loyaltyPoints;        // điểm tích lũy
    vector<string> orderHistory; // lịch sử đơn hàng
    vector<string> wishlist;     // danh sách yêu thích
public:
    Customers(string name, string id, string mail, string ph, string addr, string pass, string lp)
        : User(name, id, mail, ph, addr, pass)
    {
        loyaltyPoints = lp;
    }
    void setLoyaltyPoints(string lp) { loyaltyPoints = lp; }
    string getLoyaltyPoints() const { return loyaltyPoints; }
    void addToWishlist(const string &item)
    {
        wishlist.push_back(item);
        cout << item << " added to wishlist." << endl;
    }

    // thêm sản phẩm vào giỏ hàng
    void addToCart(const string &item)
    {
        cout << item << " added to cart." << endl;
    }
};

// --------------------Admin----------------------
class Admin : public User
{
private:
    string adminID;
    string role; // vai trò: Admin, Manager

public:
    Admin(string name, string id, string mail, string ph, string addr, string pass, string adID, string r)
        : User(name, id, mail, ph, addr, pass)
    {
        adminID = adID;
        role = r;
    }

    void setAdminID(string adID) { adminID = adID; }
    string getAdminID() const { return adminID; }
    void setRole(string r) { role = r; }
    string getRole() const { return role; }

    void manageUsers()
    {
        cout << "Admin " << getUserName() << " is managing users." << endl;
    }

    void manageProducts()
    {
        cout << "Admin " << getUserName() << " is managing products." << endl;
    }
    void viewReports()
    {
        cout << "Admin " << getUserName() << " is viewing reports." << endl;
    }
    void manageOrders()
    {
        cout << "Admin " << getUserName() << " is managing orders." << endl;
    }
    void displayAdminInfo() const
    {
        cout << "AdminID: " << adminID
             << " | Name: " << userName
             << " | Role: " << role << endl;
    }
};

// --------------------Payment----------------------
class Payment
{
private:
    string paymentID;
    string orderID;
    string paymentMethod;
    double amount;
    string paymentDate;
    string status;           // trạng thái thanh toán
    string transtactionDate; // ngày giao dịch

public:
    Payment(string pid, string oid, string method, double amt, string pdate, string sta, string tdate)
    {
        paymentID = pid;
        orderID = oid;
        paymentMethod = method;
        amount = amt;
        paymentDate = pdate;
        status = sta;
        transtactionDate = tdate;
    }

    void setPaymentID(string pid) { paymentID = pid; }
    void setOrderID(string oid) { orderID = oid; }
    void setPaymentMethod(string method) { paymentMethod = method; }
    void setAmount(double amt) { amount = amt; }
    void setPaymentDate(string pdate) { paymentDate = pdate; }
    void setStatus(string sta) { status = sta; }
    void setTranstactionDate(string tdate) { transtactionDate = tdate; }
    string getPaymentID() const { return paymentID; }
    string getOrderID() const { return orderID; }
    string getPaymentMethod() const { return paymentMethod; }
    double getAmount() const { return amount; }
    string getPaymentDate() const { return paymentDate; }
    string getStatus() const { return status; }
    string getTranstactionDate() const { return transtactionDate; }

    void processPayment()
    {
        cout << "Processing payment of amount: " << amount << " using " << paymentMethod << endl;
        status = "Completed";
        cout << "Payment status: " << status << endl;
    }

    void refundPayment()
    {
        if (status == "Completed")
        {
            cout << "Refunding payment of amount: " << amount << endl;
            status = "Refunded";
            cout << "Payment status: " << status << endl;
        }
        else
        {
            cout << "Refund not possible. Current status: " << status << endl;
        }
    }
};

//---------------------Inventory----------------------
class Inventory
{
private:
    map<string, int> stock; // productID -> quantity

public:
    void addStock(const string &pid, int qty)
    {
        stock[pid] += qty;
        cout << "Added " << qty << " units to product " << pid << ". New stock: " << stock[pid] << endl;
    }

    void removeStock(const string &pid, int qty)
    {
        if (stock.find(pid) != stock.end() && stock[pid] >= qty)
        {
            stock[pid] -= qty;
            cout << "Removed " << qty << " units from product " << pid << ". New stock: " << stock[pid] << endl;
        }
        else
        {
            cout << "Insufficient stock for product " << pid << endl;
        }
    }

    int checkStock(const string &pid) const
    {
        auto it = stock.find(pid);
        if (it != stock.end())
        {
            return it->second;
        }
        return 0; // nếu không có sản phẩm, trả về 0
    }

    bool isLowStock(const string &pid, int threshold = 5) const
    {
        auto it = stock.find(pid);
        if (it == stock.end())
            return true;
        return it->second < threshold;
    }

    void updateStock(const string &pid, int qty)
    {
        stock[pid] = qty;
    }

    void displayInventory() const
    {
        cout << "Current Inventory:" << endl;
        for (const auto &entry : stock)
        {
            cout << " - ProductID: " << entry.first << ", Quantity: " << entry.second << endl;
        }
    }
};

//---------------------Notification----------------------
class Notification
{
private:
    string notificationID;
    string userID;
    string message;
    string date;
    bool isRead;

public:
    Notification(string nid, string uid, string msg, string d)
    {
        notificationID = nid;
        userID = uid;
        message = msg;
        date = d;
        isRead = false;
    }

    void setNotificationID(string nid) { notificationID = nid; }
    void setUserID(string uid) { userID = uid; }
    void setMessage(string msg) { message = msg; }
    void setDate(string d) { date = d; }
    void markAsRead() { isRead = true; }
    string getNotificationID() const { return notificationID; }
    string getUserID() const { return userID; }
    string getMessage() const { return message; }
    string getDate() const { return date; }
    bool getIsRead() const { return isRead; }

    void displayNotification() const
    {
        cout << "NotificationID: " << notificationID
             << " | UserID: " << userID
             << " | Date: " << date
             << " | Message: " << message
             << " | Status: " << (isRead ? "Read" : "Unread") << endl;
    }
};
