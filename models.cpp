#include "models.h"


User::User(std::string login) {
    this->login = login;
    this->password = "";
    this->_is_admin = false;
}

User::User(string login, string password, bool is_admin) : login(login), password(password), _is_admin(is_admin) {};


string User::get_login() const {
    return this->login;
}

string User::get_password() {
    return this->password;
}

std::string User::get_header() {
    return get_footer() + "\n" + "|  ID  |     Логин     |    Статус    |\n" + get_footer();
}

std::string User::get_footer() {
    return "+------+---------------+--------------+";
}
void User::output_table_description(int id) {
    printf("|  %-4d| %-14s| %-17s |\n", id, get_login().data(), (is_admin() ? "Админ" : "Пользователь"));
}

Entities<string> Customer::get_menu_options(){
    return {new string[] {
                    "Список участников",
                    "Тир лист инструментов",
                    "Поиск по возврасту",
                    "Выйти"
            }, 4};
}

Entities<string> Admin::get_menu_options() {
    return {new string[] {
            "Пользователи",
            "Участники конкурса",
            "Выход"
    }, 3};
}

Entities<string> User::get_menu_options() {
    return {{}, 1};
}

User* User::deserialize(std::string data, const char* separator) {
    std::string tmp = strdup(data.data());
    tmp = strtok(tmp.data(), separator);
    std::string login = tmp;
    tmp = strtok(nullptr, separator);
    std::string password = tmp;
    tmp = strtok(nullptr, separator);
    bool is_admin = atoi(tmp.data()) == 1;
    return new User {login, password, is_admin};
}

std::string User::serialize(User user, const char* separator) {
    return user.get_login() + separator + user.get_password() + separator + (user.is_admin() ? "1" : "0");
}

string User::get_description() {
    return "Логин - " + login + "\nСтатус - " + (is_admin() ? "Админ" : "Пользователь")  + "\n";
}

void User::set_login(std::string value) {
    this->login = value;
}

void User::set_password(std::string value) {
    this->password = value;
}

bool User::operator<(const User& other) const {
    return login < other.get_login();
}

bool User::operator>(const User& other) const {
    return login > other.get_login();
}

bool User::operator==(const User& other) const {
    return login == other.get_login();
}

bool User::is_admin() {
    return this->_is_admin;
}

void User::set_admin(bool value) {
    this->_is_admin = value;
}

Customer::Customer(std::string login, std::string password, bool is_admin) : User(login, password, is_admin) {};
Customer::Customer(User user) : User(user.get_login(), user.get_password(), user.is_admin()) {};


Admin::Admin(std::string login, std::string password, bool is_admin) : User(login, password, is_admin) {};
Admin::Admin(User user) : User(user.get_login(), user.get_password(), user.is_admin()) {};

std::string Artist::get_surname() const {
    return surname;
}

std::string Artist::get_header() {
    return get_footer() + "\n" + "|  ID  |   Фамилия   | Возвраст |  Страна  |  Инструмент  | Место |\n" + get_footer();
}

std::string Artist::get_footer() {
    return "+------+-------------+----------+----------+--------------+-------+";
}

void Artist::output_table_description(int id) {
    printf("|  %-4d| %-12s| %-8d | %-8s | %-13s|  %-4d |\n", id, get_surname().data(), get_year(), get_country().data(), get_instrument().data(), get_place());
}

Artist::Artist(std::string surname, int year, std::string country, std::string instrument, int place) : surname(surname), year(year), country(country), instrument(instrument), place(place) {};

Artist::Artist(std::string surname) {
    this->surname = surname;
    year = 0;
    country = "";
    instrument = surname;
    place = 0;
}

bool Artist::operator<(const Artist& other) const {
    return surname < other.get_surname();
}

bool Artist::operator>(const Artist& other) const {
    return surname > other.get_surname();
}

bool Artist::operator==(const Artist& other) const {
    return surname == other.get_surname();
}

string Artist::get_description() {
    return "Фамилия - " + surname + "\nВозвраст - " + std::to_string(year)  + "\nСтрана - " + country + "\nИнструмент - " + instrument + "\nЗанятое место - " + std::to_string(place) + "\n";
}

int Artist::get_year() {
    return this->year;
}

std::string Artist::get_country() {
    return this->country;
}

std::string Artist::get_instrument() const{
    return this->instrument;
}

int Artist::get_place() {
    return this->place;
}

Artist* Artist::deserialize(std::string data, const char* separator) {
    std::string tmp = strdup(data.data());
    tmp = strtok(tmp.data(), separator);
    std::string surname = tmp;
    tmp = strtok(nullptr, separator);
    int year = atoi(tmp.data());
    tmp = strtok(nullptr, separator);
    std::string country = tmp.data();
    tmp = strtok(nullptr, separator);
    std::string instrument = tmp.data();
    tmp = strtok(nullptr, separator);
    int place = atoi(tmp.data());
    return new Artist {surname, year, country, instrument, place};
}

std::string Artist::serialize(Artist artist, const char* separator) {
    return artist.get_surname() + separator + std::to_string(artist.get_year()) + separator + artist.get_country() + separator + artist.get_instrument() + separator + std::to_string(artist.get_place());
}