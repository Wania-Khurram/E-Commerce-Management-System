#pragma once
#ifndef ELECTRONICSPRODUCT_H
#define ELECTRONICSPRODUCT_H

#include "Product.h"
#include <string>
using namespace std;

class ElectronicsProduct : public Product {
private:
    string brand;
    int warranty; 
public:
    ElectronicsProduct(int id, const string& name, double price, int quantity,
        double discount, int sellerId, bool approved,
        const string& brand, int warranty)
        : Product(id, name, price, quantity, discount, sellerId, approved),
        brand(brand), warranty(warranty) {
    }
    void displayDetails() const override {
        cout << "[Electronics] ";
        Product::displayDetails();
        cout << ", Brand: " << brand << ", Warranty: " << warranty << " years";
        if (!approved) cout << " (Not Approved)";
        cout << std::endl;
    }
    void applyDiscount() override {
        Product::applyDiscount();
    }
    string getBrand() const { return brand; }
    int getWarranty() const { return warranty; }
};

#endif