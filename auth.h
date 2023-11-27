//
// Created by Renat Yakublevich on 18.11.23.
//

#ifndef KURS_AUTH_H
#define KURS_AUTH_H

#include "models.h"
#include "database.hpp"
#include "sha256.h"

class Authentication {
private:
    Database<User> user_database;
public:
    Authentication(Database<User> user_database);

    User* authenticate(std::string login, std::string password);

    std::string hash_password(std::string original_password);

    void registration(std::string login, std::string password);
};


#endif //KURS_AUTH_H
