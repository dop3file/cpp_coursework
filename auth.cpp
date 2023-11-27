//
// Created by Renat Yakublevich on 18.11.23.
//

#include "auth.h"


Authentication::Authentication(Database<User> user_database) : user_database(user_database) {};

User* Authentication::authenticate(std::string login, std::string password) {
    std::string hash_password = this->hash_password(password);
    User* user = this->user_database.select(login, hash_password);
    return user;
}

std::string Authentication::hash_password(std::string original_password) {
    SHA256 sha;
    sha.update(original_password);
    std::array<uint8_t, 32> digest = sha.digest();
    return SHA256::toString(digest).substr(0,16);
    std::reverse(original_password.begin(), original_password.end());
    return original_password;
}

void Authentication::registration(std::string login, std::string password) {
    User current_user = User(
            login,
            password,
            false
    );
    this->user_database.insert(current_user);
}
