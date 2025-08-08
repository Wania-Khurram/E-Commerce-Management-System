#pragma once
#ifndef BOOKPRODUCT_H
#define BOOKPRODUCT_H

#include "Product.h"
#include <string>
using namespace std;

class BookProduct : public Product {
private:
    string author;
public:
    BookProduct(int id, const string& name, double price, int quantity,
        double discount, int sellerId, bool approved,
        const string& author)
        : Product(id, name, price, quantity, discount, sellerId, approved),
        author(author) {
    }
    void displayDetails() const override {
        cout << "[Book] ";
        Product::displayDetails();
        cout << ", Author: " << author;
        if (!approved) cout << " (Not Approved)";
        cout << std::endl;
    }
    void applyDiscount() override {
        Product::applyDiscount();
    }
    string getAuthor() const { return author; }
};

#endif