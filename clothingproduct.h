#pragma once
#ifndef CLOTHINGPRODUCT_H
#define CLOTHINGPRODUCT_H

#include "Product.h"
#include <string>
using namespace std;

class ClothingProduct : public Product {
private:
    string size;
    string color;
public:
    ClothingProduct(int id, const string& name, double price, int quantity,
        double discount, int sellerId, bool approved,
        const string& size, const string& color)
        : Product(id, name, price, quantity, discount, sellerId, approved),
        size(size), color(color) {
    }
    void displayDetails() const override {
        cout << "[Clothing] ";
        Product::displayDetails();
        cout << ", Size: " << size << ", Color: " << color;
        if (!approved) cout << " (Not Approved)";
        cout << endl;
    }
    void applyDiscount() override {
        Product::applyDiscount();
    }
    string getSize() const { return size; }
    string getColor() const { return color; }
};

#endif