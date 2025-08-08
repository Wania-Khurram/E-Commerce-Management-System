#pragma once
#ifndef AUTHSYSTEM_H
#define AUTHSYSTEM_H

#include <iostream>
#include <vector>
#include <string>
#include<algorithm>
#include "User.h"
#include "Seller.h"
#include "Buyer.h"
using namespace std;

class AuthSystem {
public:
    static User* login(const vector<User*>& users) {
        string name, password;
        cout << "Enter username: ";
        cin >> name;
        cout << "Enter password: ";
        cin >> password;
        for (auto* user : users) {
            if (user->getName() == name && user->getPassword() == password) {
                cout << "Login successful! Welcome, " << user->getName() << ".\n";
                return user;
            }
        }
        cout << "Invalid username or password.\n";
        return nullptr;
    }
    static User* registerUser(vector<User*>& users) {
        string type;
        cout << "Register as (Buyer/Seller): ";
        cin >> type;
        if (type != "Buyer" && type != "buyer"  && type!="seller" && type != "Seller") {
            cout << "Invalid type.\n";
            return nullptr;
        }
        string name, password;
        cout << "Enter username: ";
        cin >> name;
        for (auto* user : users) {
            if (user->getName() == name) {
                cout << "Username already taken.\n";
                return nullptr;
            }
        }
        cout << "Enter password: ";
        cin >> password;
        int id = User::getNextId();
        User* newUser;
        transform(type.begin(), type.end(), type.begin(), ::tolower);
        if (type=="seller") {
            newUser = new Seller(id, name, password);
        }
        else {
            newUser = new Buyer(id, name, password);
        }
        users.push_back(newUser);
        cout << type << " registered successfully! Your ID is " << id << ".\n";
        return newUser;
    }
};

#endif