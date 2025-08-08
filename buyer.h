#pragma once
#ifndef BUYER_H
#define BUYER_H

#include "User.h"
#include "Cart.h"
using namespace std;

class Product; 

class Buyer : public User {
private:
    Cart<Product*> cart;
public:
    Buyer(int id, const string& name, const string& password)
        : User(id, name, password, "Buyer"), cart() {
    }
    Cart<Product*>& getCart() { return cart; }
};

#endif