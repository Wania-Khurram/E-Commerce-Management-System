#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"
using namespace std;

class Admin : public User {
public:
    Admin(int id, const string& name, const string& password)
        : User(id, name, password, "Admin") {
    }
};

#endif
