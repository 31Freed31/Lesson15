#include <iostream>
#include <map>
#include <stdexcept>
#include <string>

using namespace std;

class ShoppingCart {
private:
    map<string, int> shop;
    map<string, int> cart;
public:
    void addToShop(const string& article, int quantity) {
        if (quantity <= 0) {
            throw invalid_argument("Quantity must be positive");
        }
        shop[article] += quantity;
    }

    void add(const string& article, int quantity) {
        if (shop.find(article) == shop.end()) {
            throw invalid_argument("Article not found in shop");
        }
        if (quantity <= 0 || quantity > shop[article]) {
            throw runtime_error("Invalid quantity");
        }
        cart[article] += quantity;
        shop[article] -= quantity;
    }

    void remove(const string& article, int quantity) {
        if (cart.find(article) == cart.end()) {
            throw invalid_argument("Article not found in cart");
        }
        if (quantity <= 0 || quantity > cart[article]) {
            throw runtime_error("Invalid quantity");
        }
        cart[article] -= quantity;
        shop[article] += quantity;

        if (cart[article] == 0) {
            cart.erase(article);
        }
    }

    void displayCart() const {
        cout << "Shopping Cart:" << endl;
        if (cart.empty()) {
            cout << "Your cart is empty." << endl;
        }
        else {
            for (const auto& item : cart) {
                cout << "Article: " << item.first << ", Quantity: " << item.second << endl;
            }
        }
    }

    void displayShop() const {
        cout << "Shop Inventory:" << endl;
        for (const auto& item : shop) {
            cout << "Article: " << item.first << ", Available: " << item.second << endl;
        }
    }
};

int main() {
    ShoppingCart cart;

    cart.addToShop("Item1", 10);
    cart.addToShop("Item2", 5);

    string command, article;
    int quantity;

    while (true) {
        cout << "Enter command (add, remove, show_cart, show_shop, exit): ";
        cin >> command;

        try {
            if (command == "add") {
                cout << "Enter article and quantity: ";
                cin >> article >> quantity;
                cart.add(article, quantity);
            }
            else if (command == "remove") {
                cout << "Enter article and quantity: ";
                cin >> article >> quantity;
                cart.remove(article, quantity);
            }
            else if (command == "show_cart") {
                cart.displayCart();
            }
            else if (command == "show_shop") {
                cart.displayShop();
            }
            else if (command == "exit") {
                break;
            }
            else {
                cout << "Unknown command!" << endl;
            }
        }
        catch (const invalid_argument& e) {
            cerr << "Error: " << e.what() << endl;
        }
        catch (const runtime_error& e) {
            cerr << "Error: " << e.what() << endl;
        }
    }
    return 0;
}
