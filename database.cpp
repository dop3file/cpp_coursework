//
// Created by Renat Yakublevich on 20.11.23.
//
#include "database.hpp"

template <typename T>
User* Database<T>::select(std::string in_login, std::string in_password) {
    std::ifstream database;
    database.open(this->file_path);
    std::string buffer;
    std::string user_login;
    std::string user_password;
    User* current_user;
    if (database.is_open())
    {

        while (std::getline(database, buffer))
        {
            current_user = serialize(buffer);
            if (current_user->get_login() == in_login && current_user->get_password() == in_password) {
                if (current_user->is_admin()) return new Admin(*current_user);
                return new Customer(*current_user);
            }
        }
    }
    database.close();
    return nullptr;
}


template <typename T>
void Database<T>::insert(T object) {
    std::ofstream file;
    file.open(this->file_path, std::ios::out | std::ios::app);
    if (file.is_open())
    {
        file << object.serialize(object, this->separator) << std::endl;
    }

    file.close();
}

template <typename T>
void Database<T>::clear() {
    std::ofstream ofs;
    ofs.open(file_path, std::ofstream::out | std::ofstream::trunc);
    ofs.close();
}

template <typename T>
T* Database<T>::serialize(std::string line) {
    return T::deserialize(line, this->separator);
}


template <typename T>
Collection<T>* Database<T>::select_all() {
    std::ifstream database;
    database.open(this->file_path);
    std::string buffer;
    auto* collection = new Collection<T>;
    int user_index = 0;
    if (database.is_open())
    {
        while (std::getline(database, buffer))
        {
            if (strlen(buffer.c_str()) <= 5) continue;
            collection->insert(*serialize(buffer));
            user_index++;
        }
    }
    database.close();
    return collection;
}


template Artist* Database<Artist>::serialize(std::string line);
template User* Database<User>::serialize(std::string line);

template User* Database<User>::select(std::string in_login, std::string in_password);

template Collection<User>* Database<User>::select_all();
template Collection<Artist>* Database<Artist>::select_all();

template void Database<User>::clear();
template void Database<Artist>::clear();

template void Database<User>::insert(User object);
template void Database<Artist>::insert(Artist object);