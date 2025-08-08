#pragma once
#ifndef USER_H
#define USER_H

#include <string>
using namespace std;

class User {
protected:
    int id;
    string name;
    string password;
    string type; // "Admin", "Seller", or "Buyer"
    static int nextId;
public:
    User(int id, const string& name, const string& password, const string& type)
        : id(id), name(name), password(password), type(type) {
    }
    virtual ~User() {}
    int getId() const { return id; }
    string getName() const { return name; }
    string getPassword() const { return password; }
    string getType() const { return type; }
    static int getNextId() { return nextId++; }
    static void setNextId(int id) { nextId = id; }
};

#endif