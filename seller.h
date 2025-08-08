#pragma once
#ifndef SELLER_H
#define SELLER_H

#include "User.h"
using namespace std;

class Seller : public User {
public:
    Seller(int id, const string& name, const string& password)
        : User(id, name, password, "Seller") {
    }
};

#endif