#ifndef KURS_MODELS_H
#define KURS_MODELS_H


#include <iostream>
#include "collection.h"

#define MAX_COUNT_ENTITIES 1024

using namespace std;



class Artist {
public:
    bool operator<(const Artist& other) const;
    bool operator>(const Artist& other) const;
    bool operator==(const Artist& other) const;

    std::string get_surname() const;

    Artist(std::string surname, int year, std::string country, std::string instrument, int place);
    Artist(std::string surname);
    Artist() {};

    std::string get_description();
    int get_year();
    std::string get_country();
    std::string get_instrument() const;
    int get_place();

    static Artist* deserialize(std::string data, const char* separator);

    static std::string serialize(Artist artist, const char* separator);

    static std::string get_header();

    static std::string get_footer();

    void output_table_description(int id);

private:
    std::string surname;
    int year;
    std::string country;
    std::string instrument;
    int place;
};


class User {
private:
    std::string login;
    std::string password;
    bool _is_admin;
public:
    User(std::string login, std::string password, bool is_admin);
    User() {};
    User(std::string login);

    string get_login() const;

    string get_password();

    string get_description();

    void set_login(std::string value);

    void set_password(std::string value);

    bool is_admin();

    void set_admin(bool value);

    virtual Entities<string> get_menu_options();

    static User* deserialize(std::string data, const char* separator);

    static std::string serialize(User user, const char* separatorr);

    static std::string get_header();

    static std::string get_footer();

    void output_table_description(int id);

    bool operator<(const User& other) const;
    bool operator>(const User& other) const;
    bool operator==(const User& other) const;
};


class Customer : public User {
public:
    Customer(std::string login, std::string password, bool is_admin);
    Customer(User user);
    Entities<string> get_menu_options();
};


class Admin : public User {
public:
    Admin(std::string login, std::string password, bool is_admin);
    Admin(User user);
    Entities<string> get_menu_options();
};
#endif //KURS_MODELS_H
