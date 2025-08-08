#pragma once
#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "User.h"
#include "Admin.h"
#include "Seller.h"
#include "Buyer.h"
#include "Product.h"
#include "ElectronicProduct.h"
#include "ClothingProduct.h"
#include "BookProduct.h"
#include "Order.h"
using namespace std;

class FileManager {
public:
    static void loadUsers(const string& filename, vector<User*>& users) {
        ifstream file(filename);
        if (!file) return;
        string line;
        int maxId = 0;
        while (getline(file, line)) {
            if (line.empty()) continue;
            stringstream ss(line);
            string type;
            getline(ss, type, ',');
            string idStr;
            getline(ss, idStr, ','); int id = stoi(idStr);
            string name, password;
            getline(ss, name, ',');
            getline(ss, password, ',');
            if (type == "Admin") {
                users.push_back(new Admin(id, name, password));
            }
            else if (type == "Seller") {
                users.push_back(new Seller(id, name, password));
            }
            else if (type == "Buyer") {
                users.push_back(new Buyer(id, name, password));
            }
            if (id > maxId) maxId = id;
        }
        User::setNextId(maxId + 1);
        file.close();
    }
    static void saveUsers(const string& filename, const vector<User*>& users) {
        ofstream file(filename);
        for (const auto& user : users) {
            file << user->getType() << "," << user->getId() << ","
                << user->getName() << "," << user->getPassword() << "\n";
        }
        file.close();
    }

    static void loadProducts(const string& filename, vector<Product*>& products) {
        ifstream file(filename);
        if (!file) return;
        string line;
        int maxId = 0;
        while (getline(file, line)) {
            if (line.empty()) continue;
            stringstream ss(line);
            string type;
            getline(ss, type, ',');
            string idStr, priceStr, quantityStr, discountStr, sellerIdStr, approvedStr;
            getline(ss, idStr, ','); int id = std::stoi(idStr);
            string name;
            getline(ss, name, ',');
            getline(ss, priceStr, ','); double price = stod(priceStr);
            getline(ss, quantityStr, ','); int quantity = stoi(quantityStr);
            getline(ss, discountStr, ','); double discount = stod(discountStr);
            getline(ss, sellerIdStr, ','); int sellerId = stoi(sellerIdStr);
            getline(ss, approvedStr, ','); bool approved = (approvedStr == "1");
            if (type == "Electronics") {
                string brand, warrantyStr;
                getline(ss, brand, ',');
                getline(ss, warrantyStr, ',');
                int warranty = stoi(warrantyStr);
                products.push_back(new ElectronicsProduct(id, name, price, quantity, discount, sellerId, approved, brand, warranty));
            }
            else if (type == "Clothing") {
                string size, color;
                getline(ss, size, ',');
                getline(ss, color, ',');
                products.push_back(new ClothingProduct(id, name, price, quantity, discount, sellerId, approved, size, color));
            }
            else if (type == "Book") {
                string author;
                getline(ss, author, ',');
                products.push_back(new BookProduct(id, name, price, quantity, discount, sellerId, approved, author));
            }
            if (id > maxId) maxId = id;
        }
        Product::setNextId(maxId + 1);
        file.close();
    }
    static void saveProducts(const std::string& filename, const std::vector<Product*>& products) {
        ofstream file(filename);
        for (const auto& prod : products) {
            if (ElectronicsProduct* e = dynamic_cast<ElectronicsProduct*>(prod)) {
                file << "Electronics," << e->getId() << "," << e->getName() << ","
                    << e->getPrice() << "," << e->getQuantity() << ","
                    << e->getDiscount() << "," << e->getSellerId() << ","
                    << (e->isApproved() ? "1" : "0") << ","
                    << e->getBrand() << "," << e->getWarranty() << "\n";
            }
            else if (ClothingProduct* c = dynamic_cast<ClothingProduct*>(prod)) {
                file << "Clothing," << c->getId() << "," << c->getName() << ","
                    << c->getPrice() << "," << c->getQuantity() << ","
                    << c->getDiscount() << "," << c->getSellerId() << ","
                    << (c->isApproved() ? "1" : "0") << ","
                    << c->getSize() << "," << c->getColor() << "\n";
            }
            else if (BookProduct* b = dynamic_cast<BookProduct*>(prod)) {
                file << "Book," << b->getId() << "," << b->getName() << ","
                    << b->getPrice() << "," << b->getQuantity() << ","
                    << b->getDiscount() << "," << b->getSellerId() << ","
                    << (b->isApproved() ? "1" : "0") << ","
                    << b->getAuthor() << "\n";
            }
        }
        file.close();
    }

    static void loadOrders(const string& filename, vector<Order>& orders, const vector<Product*>& products) {
        ifstream file(filename);
        if (!file) return;
        string line;
        int maxId = 0;
        while (getline(file, line)) {
            if (line.empty()) continue;
            stringstream ss(line);
            string label;
            getline(ss, label, ',');
            if (label == "Order") {
                string idStr, buyerStr, totalStr, countStr;
                getline(ss, idStr, ',');
                getline(ss, buyerStr, ',');
                getline(ss, totalStr, ',');
                getline(ss, countStr, ',');
                int orderId = stoi(idStr);
                int buyerId = stoi(buyerStr);
                int count = stoi(countStr);
                Order order(orderId, buyerId);
                for (int i = 0; i < count; ++i) {
                    string itemLine;
                    getline(file, itemLine);
                    stringstream ss2(itemLine);
                    string pidStr, qtyStr;
                    getline(ss2, pidStr, ',');
                    getline(ss2, qtyStr, ',');
                    int pid = stoi(pidStr);
                    int qty = stoi(qtyStr);
                    Product* prodPtr = nullptr;
                    for (auto* p : products) {
                        if (p->getId() == pid) { prodPtr = p; break; }
                    }
                    if (prodPtr) {
                        order.addItem(prodPtr, qty);
                        prodPtr->setQuantity(prodPtr->getQuantity() - qty);
                    }
                }
                orders.push_back(order);
                if (orderId > maxId) maxId = orderId;
            }
        }
        Order::setNextId(maxId + 1);
        file.close();
    }
    static void saveOrders(const string& filename, const vector<Order>& orders) {
        ofstream file(filename);
        for (const auto& order : orders) {
            const auto& items = order.getItems();
            file << "Order," << order.getOrderId() << "," << order.getBuyerId() << ","
                << order.getTotal() << "," << items.size() << "\n";
            for (const auto& p : items) {
                file << p.first->getId() << "," << p.second << "\n";
            }
        }
        file.close();
    }
};

#endif