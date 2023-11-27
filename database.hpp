#ifndef KURS_DATABASE_HPP
#define KURS_DATABASE_HPP

#include "models.h"
#include <iostream>
#include <fstream>


template<typename T>
class Database {
public:
    void insert(T object);

    User* select(std::string in_login, std::string in_password);

    T* serialize(std::string line);

    Collection<T>* select_all();

    void clear();

    Database(const std::string file_path) : file_path(file_path) {};

private:
    std::string file_path;
    std::string extension;
    const char* separator = ";";
    const int MAX_RECORDS = 1028;
};


#endif //KURS_DATABASE_HPP
