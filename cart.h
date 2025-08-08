#pragma once
#ifndef CART_H
#define CART_H

#include <iostream>
#include <vector>
#include <iomanip>
#include <stdexcept>
using namespace std;

template<typename T>
class Cart {
private:
    vector<pair<T, int>> items;
public:
    Cart() {}
    void addItem(T item) {
        if (item == nullptr) throw invalid_argument("Null product");
        if (item->getQuantity() <= 0) {
            throw runtime_error("Product out of stock: " + item->getName());
        }
        for (auto& p : items) {
            if (p.first == item) {
                p.second++;
                return;
            }
        }
        items.push_back({ item, 1 });
    }
    void removeItem(T item) {
        for (auto it = items.begin(); it != items.end(); ++it) {
            if (it->first == item) {
                it->second--;
                if (it->second <= 0) items.erase(it);
                return;
            }
        }
    }
    double getTotal() const {
        double total = 0;
        for (const auto& p : items) {
            total += p.first->getPrice() * p.second;
        }
        return total;
    }
    const vector<pair<T, int>>& getItems() const { return items; }
    friend ostream& operator<<(ostream& os, const Cart<T>& cart) {
        if (cart.items.empty()) {
            os << "Cart is empty.\n";
        }
        else {
            os << "Cart items:\n";
            for (const auto& p : cart.items) {
                os << p.first->getName() << " (ID: " << p.first->getId() << ") x" << p.second
                    << " - $" << fixed << setprecision(2)
                    << (p.first->getPrice() * p.second) << "\n";
            }
            os << "Total: $" << fixed << setprecision(2) << cart.getTotal() << "\n";
        }
        return os;
    }
    void operator+=(T item) { addItem(item); }
    void operator-=(T item) { removeItem(item); }
};

#endif