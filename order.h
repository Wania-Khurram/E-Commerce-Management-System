#pragma once
#ifndef ORDER_H
#define ORDER_H

#include <vector>
#include "Product.h"
#include <iostream>
using namespace std;

class Order {
private:
    int orderId;
    int buyerId;
    vector<pair<Product*, int>> items;
    double total;
    static int nextId;
public:
    Order(int id, int buyerId) : orderId(id), buyerId(buyerId), total(0) {}
    int getOrderId() const { return orderId; }
    int getBuyerId() const { return buyerId; }
    double getTotal() const { return total; }
    void addItem(Product* product, int quantity) {
        items.push_back({ product, quantity });
        total += product->getPrice() * quantity;
    }
    void displayOrder() const {
        cout << "Order ID: " << orderId << ", Buyer ID: " << buyerId << "\n";
        cout << "Items:\n";
        for (const auto& p : items) {
            cout << "- " << p.first->getName() << " x" << p.second << " = $"
                << fixed << setprecision(2)
                << (p.first->getPrice() * p.second) << "\n";
        }
        cout << "Total: $" << fixed << setprecision(2) << total << "\n";
    }
    static int getNextId() { return nextId++; }
    static void setNextId(int id) { nextId = id; }
    const vector<pair<Product*, int>>& getItems() const { return items; }
};

#endif