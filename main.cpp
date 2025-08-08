#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <string>
#include "Admin.h"
#include "Seller.h"
#include "Buyer.h"
#include "ElectronicProduct.h"
#include "ClothingProduct.h"
#include "BookProduct.h"
#include "FileManager.h"
#include "AuthSystem.h"
using namespace std;

void adminMenu(User* user, vector<User*>& users, vector<Product*>& products, vector<Order>& orders) {
    while (true) {
        cout << "\n--- Admin Menu ---\n";
        cout << "1. Manage Users\n";
        cout << "2. Approve Products\n";
        cout << "3. View Reports\n";
        cout << "4. Logout\n";
        cout << "Choose an option: ";
        int choice;
        cin >> choice;
        if (choice == 1) {
            cout << "\nUsers:\n";
            for (auto* u : users) {
                cout << u->getId() << ": " << u->getName() << " (" << u->getType() << ")\n";
            }
            cout << "Enter user ID to delete (or 0 to cancel): ";
            int uid;
            cin >> uid;
            if (uid == 0) continue;
            bool found = false;
            for (auto it = users.begin(); it != users.end(); ++it) {
                if ((*it)->getId() == uid) {
                    if ((*it)->getType() == "Admin") {
                        cout << "Cannot delete Admin user.\n";
                    }
                    else {
                        delete* it;
                        users.erase(it);
                        FileManager::saveUsers("users.txt", users);
                        cout << "User deleted.\n";
                    }
                    found = true;
                    break;
                }
            }
            if (!found) cout << "User ID not found.\n";
        }
        else if (choice == 2) {
            cout << "\nProducts awaiting approval:\n";
            for (auto* p : products) {
                if (!p->isApproved()) {
                    p->displayDetails();
                }
            }
            cout << "Enter product ID to approve (or 0 to cancel): ";
            int pid;
            cin >> pid;
            if (pid == 0) continue;
            bool found = false;
            for (auto* p : products) {
                if (p->getId() == pid) {
                    p->setApproved(true);
                    FileManager::saveProducts("products.txt", products);
                    cout << "Product approved.\n";
                    found = true;
                    break;
                }
            }
            if (!found) cout << "Product ID not found or already approved.\n";
        }
        else if (choice == 3) {
            cout << "\n--- Sales Report ---\n";
            double totalRevenue = 0;
            for (const auto& o : orders) {
                totalRevenue += o.getTotal();
            }
            cout << "Total Orders: " << orders.size() << "\n";
            cout << "Total Revenue: $" << fixed << setprecision(2) << totalRevenue << "\n";
        }
        else if (choice == 4) {
            break;
        }
        else {
            cout << "Invalid choice.\n";
        }
    }
}

void sellerMenu(Seller* seller, vector<Product*>& products, vector<Order>& orders) {
    while (true) {
        cout << "\n--- Seller Menu ---\n";
        cout << "1. Add Product\n";
        cout << "2. Update Product\n";
        cout << "3. Delete Product\n";
        cout << "4. View Orders\n";
        cout << "5. Logout\n";
        cout << "Choose an option: ";
        int choice;  
        cin >> choice;
        if (choice == 1) {
            cout << "\nEnter product category (Electronics/Clothing/Book): ";
            string category;
            cin >> category;
            cout << "Enter product name: ";
            cin.ignore();
            string name; getline(cin, name);
            cout << "Enter price: ";
            double price; cin >> price;
            std::cout << "Enter quantity: ";
            int quantity;
            cin >> quantity;
            cout << "Enter discount percentage: ";
            double discount;
            cin >> discount;
            int id = Product::getNextId();
            if (category == "Electronics" || category=="electronics") {
                string brand; int warranty;
                cout << "Enter brand: ";
                cin.ignore();
                getline(cin, brand);
                cout << "Enter warranty (years): ";
                cin >> warranty;
                auto* p = new ElectronicsProduct(id, name, price, quantity, discount, seller->getId(), false, brand, warranty);
                p->applyDiscount();
                products.push_back(p);
            }
            else if (category == "Clothing" || category == "clothing") {
                string size, color;
                cout << "Enter size: ";
                cin.ignore();
                getline(cin, size);
                cout << "Enter color: ";
                getline(cin, color);
                auto* p = new ClothingProduct(id, name, price, quantity, discount, seller->getId(), false, size, color);
                p->applyDiscount();
                products.push_back(p);
            }
            else if (category == "Book" || category == "book") {
                string author;
                cout << "Enter author: ";
                cin.ignore();
                getline(cin, author);
                auto* p = new BookProduct(id, name, price, quantity, discount, seller->getId(), false, author);
                p->applyDiscount();
                products.push_back(p);
            }
            else {
                cout << "Invalid category.\n";
                continue;
            }
            FileManager::saveProducts("products.txt", products);
            cout << "Product added. ID: " << id << ". Pending approval.\n";
        }
        else if (choice == 2) {
            cout << "\nYour Products:\n";
            for (auto* p : products) {
                if (p->getSellerId() == seller->getId()) {
                    p->displayDetails();
                }
            }
            cout << "Enter product ID to update (or 0 to cancel): ";
            int pid; cin >> pid;
            if (pid == 0) continue;
            bool found = false;
            for (auto* p : products) {
                if (p->getId() == pid && p->getSellerId() == seller->getId()) {
                    found = true;
                    cout << "Enter new name (or 'no' to skip): ";
                    cin.ignore();
                    string newName; getline(cin, newName);
                    if (newName != "no" && !newName.empty()) p->setName(newName);
                    cout << "Enter new price (or 0 to skip): ";
                    double newPrice;
                    cin >> newPrice;
                    if (newPrice > 0) p->setPrice(newPrice);
                    cout << "Enter new quantity (or -1 to skip): ";
                    int newQty;
                    cin >> newQty;
                    if (newQty >= 0) p->setQuantity(newQty);
                    FileManager::saveProducts("products.txt", products);
                    cout << "Product updated.\n";
                    break;
                }
            }
            if (!found) cout << "Product not found.\n";
        }
        else if (choice == 3) {
            cout << "\nYour Products:\n";
            for (auto* p : products) {
                if (p->getSellerId() == seller->getId()) {
                    p->displayDetails();
                }
            }
            cout << "Enter product ID to delete (or 0 to cancel): ";
            int pid; std::cin >> pid;
            if (pid == 0) continue;
            bool found = false;
            for (auto it = products.begin(); it != products.end(); ++it) {
                if ((*it)->getId() == pid && (*it)->getSellerId() == seller->getId()) {
                    delete* it;
                    products.erase(it);
                    FileManager::saveProducts("products.txt", products);
                    cout << "Product deleted.\n";
                    found = true;
                    break;
                }
            }
            if (!found) cout << "Product not found.\n";
        }
        else if (choice == 4) {
            cout << "\nOrders containing your products:\n";
            for (const auto& o : orders) {
                bool printedOrder = false;
                for (const auto& item : o.getItems()) {
                    if (item.first->getSellerId() == seller->getId()) {
                        if (!printedOrder) {
                            cout << "Order ID: " << o.getOrderId()
                                << " | Buyer ID: " << o.getBuyerId() << "\n";
                            printedOrder = true;
                        }
                        cout << " - " << item.first->getName()
                            << " x" << item.second << "\n";
                    }
                }
            }
        }
        else if (choice == 5) {
            break;
        }
        else {
            cout << "Invalid choice.\n";
        }
    }
}

void buyerMenu(Buyer* buyer, vector<Product*>& products, vector<Order>& orders) {
    while (true) {
        cout << "\n--- Buyer Menu ---\n";
        cout << "1. Browse Products\n";
        cout << "2. Search Products\n";
        cout << "3. View Cart\n";
        cout << "4. Checkout\n";
        cout << "5. Logout\n";
        cout << "Choose an option: ";
        int choice;
        cin >> choice;
        if (choice == 1) {
            cout << "\nAvailable Products:\n";
            cout << "Filter by category (Electronics/Clothing/Book/All): ";
            string cat;
            cin >> cat;
            vector<Product*> filtered;
            for (auto* p : products) {
                if (!p->isApproved()) continue;
                if (cat == "All" || cat=="all") {
                    filtered.push_back(p);
                }
                else if ((cat == "Electronics" || cat == "electronics") && dynamic_cast<ElectronicsProduct*>(p)) {
                    filtered.push_back(p);
                }
                else if ((cat == "Clothing" || cat == "clothing") && dynamic_cast<ClothingProduct*>(p)) {
                    filtered.push_back(p);
                }
                else if ((cat == "Book" || cat == "book") && dynamic_cast<BookProduct*>(p)) {
                    filtered.push_back(p);
                }
            }
            if (filtered.empty()) {
                cout << "No products found.\n";
            }
            else {
                cout << "Sort by price? (asc/desc/none): ";
                string order;
                cin >> order;
                if (order == "asc") {
                    sort(filtered.begin(), filtered.end(), [](Product* a, Product* b) {
                        return a->getPrice() < b->getPrice();
                        });
                }
                else if (order == "desc") {
                    sort(filtered.begin(), filtered.end(), [](Product* a, Product* b) {
                        return a->getPrice() > b->getPrice();
                        });
                }
                for (auto* p : filtered) {
                    p->displayDetails();
                }
                cout << "Enter product ID to add to cart (or 0 to skip): ";
                int pid;
                cin >> pid;
                if (pid != 0) {
                    Product* sel = nullptr;
                    for (auto* p : filtered) {
                        if (p->getId() == pid) {
                            sel = p; break;
                        }
                    }
                    if (sel) {
                        try {
                            buyer->getCart() += sel;
                            cout << "Product added to cart.\n";
                        }
                        catch (const exception& e) {
                            cout << e.what() << "\n";
                        }
                    }
                    else {
                        cout << "Product not found.\n";
                    }
                }
            }
        }
        else if (choice == 2) {
            cout << "Enter search term: ";
            string term;
            cin.ignore();
            getline(cin, term);
            bool found = false;
            for (auto* p : products) {
                if (p->isApproved() && p->getName().find(term) != string::npos) {
                    p->displayDetails();
                    found = true;
                }
            }
            if (!found) {
                cout << "No products found.\n";
            }
            else {
                cout << "Enter product ID to add to cart (or 0 to skip): ";
                int pid;
                cin >> pid;
                if (pid != 0) {
                    Product* sel = nullptr;
                    for (auto* p : products) {
                        if (p->getId() == pid && p->isApproved()) {
                            sel = p; break;
                        }
                    }
                    if (sel) {
                        try {
                            buyer->getCart() += sel;
                            cout << "Product added to cart.\n";
                        }
                        catch (const exception& e) {
                            cout << e.what() << "\n";
                        }
                    }
                    else {
                        cout << "Product not found.\n";
                    }
                }
            }
        }
        else if (choice == 3) {
            cout << buyer->getCart();
            cout << "Enter product ID to remove from cart (or 0 to skip): ";
            int pid;
            cin >> pid;
            if (pid != 0) {
                Product* rem = nullptr;
                for (auto* p : products) {
                    if (p->getId() == pid) {
                        rem = p; break;
                    }
                }
                if (rem) {
                    buyer->getCart() -= rem;
                    cout << "Product removed from cart.\n";
                }
                else {
                    cout << "Product not found in cart.\n";
                }
            }
        }
        else if (choice == 4) {
            Cart<Product*>& cart = buyer->getCart();
            if (cart.getTotal() == 0) {
                cout << "Cart is empty.\n";
                continue;
            }
            double total = cart.getTotal();
            cout << "Total amount: $" << std::fixed << setprecision(2) << total << "\n";
            cout << "Proceed to checkout? (yes/no): ";
            string yn; std::cin >> yn;
            if (yn == "yes") {
                int orderId = Order::getNextId();
                Order order(orderId, buyer->getId());
                for (const auto& p : cart.getItems()) {
                    order.addItem(p.first, p.second);
                    p.first->setQuantity(p.first->getQuantity() - p.second);
                }
                orders.push_back(order);
                FileManager::saveOrders("orders.txt", orders);
                FileManager::saveProducts("products.txt", products);
                cart = Cart<Product*>(); 
                cout << "Order placed. Order ID: " << orderId << "\n";
            }
        }
        else if (choice == 5) {
            break;
        }
        else {
            cout << "Invalid choice.\n";
        }
    }
}

int main() {
    vector<User*> users;
    vector<Product*> products;
    vector<Order> orders;
    FileManager::loadUsers("users.txt", users);
    FileManager::loadProducts("products.txt", products);
    FileManager::loadOrders("orders.txt", orders, products);

    bool adminExists = false;
    for (auto* u : users) {
        if (u->getType() == "Admin") { adminExists = true; break; }
    }
    if (!adminExists) {
        int id = User::getNextId();
        users.push_back(new Admin(id, "admin", "admin"));
        FileManager::saveUsers("users.txt", users);
    }
    cout << "Default admin created (username: admin, password: admin).\n";

    while (true) {
        cout << "\n=== E-Commerce Management System ===\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Choose an option: ";
        int choice;
        cin >> choice;
        if (choice == 1) {
            User* newUser = AuthSystem::registerUser(users);
            if (newUser) {
                FileManager::saveUsers("users.txt", users);
            }
        }
        else if (choice == 2) {
            User* user = AuthSystem::login(users);
            if (!user) continue;
            if (user->getType() == "Admin") {
                adminMenu(user, users, products, orders);
            }
            else if (user->getType() == "Seller") {
                sellerMenu(dynamic_cast<Seller*>(user), products, orders);
            }
            else if (user->getType() == "Buyer") {
                buyerMenu(dynamic_cast<Buyer*>(user), products, orders);
            }
            FileManager::saveProducts("products.txt", products);
            FileManager::saveOrders("orders.txt", orders);
        }
        else if (choice == 3) {
            cout << "Exiting...\n";
            break;
        }
        else {
            cout << "Invalid choice.\n";
        }
    }

    for (auto* u : users) delete u;
    for (auto* p : products) delete p;
    return 0;
}