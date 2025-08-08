#pragma once
#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

class Product {
protected:
    int id;
    string name;
    double price;
    int quantity;
    double discount; 
    int sellerId;
    bool approved;
    static int nextId;
public:
    Product(int id, const string& name, double price, int quantity,
        double discount, int sellerId, bool approved)
        : id(id), name(name), price(price), quantity(quantity),
        discount(discount), sellerId(sellerId), approved(approved) {
    }
    virtual ~Product() {}
    virtual void displayDetails() const {
        std::cout << "ID: " << id << ", Name: " << name
            << ", Price: $" << fixed << std::setprecision(2) << price
            << ", Quantity: " << quantity;
    }
    virtual void applyDiscount() {
        price -= price * (discount / 100.0);
    }
    int getId() const { return id; }
    string getName() const { return name; }
    double getPrice() const { return price; }
    int getQuantity() const { return quantity; }
    void setQuantity(int q) { quantity = q; }
    double getDiscount() const { return discount; }
    int getSellerId() const { return sellerId; }
    bool isApproved() const { return approved; }
    void setApproved(bool app) { approved = app; }
    void setName(const string& n) { name = n; }
    void setPrice(double p) { price = p; }
    static int getNextId() { return nextId++; }
    static void setNextId(int id) { nextId = id; }
};

#endif