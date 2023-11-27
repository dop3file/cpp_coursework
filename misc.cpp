//
// Created by Renat Yakublevich on 18.11.23.
//

#include "misc.h"


bool user_exists(std::string login, Entities<User> users) {
    for (int i = 0; i < users.length; ++i) {
        if (users.entities[i].get_login() == login) return true;
    }
    return false;
}

bool str_exists(std::string str, std::string* arr, int length) {
    for (int i = 0; i < length; ++i) {
        if (arr[i] == str) return true;
    }
    return false;
}

void sort_by_place(Entities<Artist>* artists) {
    for (int i = 0; i < artists->length - 1; i++) {
        int minIndex = i;

        for (int j = i + 1; j < artists->length; j++) {
            if (artists->entities[j].get_place() < artists->entities[minIndex].get_place()) {
                minIndex = j;
            }
        }

        swap(artists->entities[i], artists->entities[minIndex]);
    }
}

std::string get_date() {
    std::time_t currentTime = std::time(nullptr);

    std::tm* currentDate = std::localtime(&currentTime);

    int year = currentDate->tm_year + 1900;
    int month = currentDate->tm_mon + 1;
    int day = currentDate->tm_mday;
    int hours = currentDate->tm_hour;
    int minutes = currentDate->tm_min;
    int seconds = currentDate->tm_sec;

    return to_string(day) + "." + to_string(month) + "." + to_string(year) + " " + to_string(hours) + ":" + to_string(minutes) + ":" + to_string(seconds);
}

std::string Color::get_colorfull_text(std::string text, int color_code) {
    return using_color ? "\033[" + to_string(color_code) + "m" + text + reset() : text;
}

std::string Color::get_italic_text(std::string text) {
    return using_color ? "\033[3m" + text + reset() : text;
}

std::string Color::get_bold_text(std::string text) {
    return using_color ? "\033[1m" + text + reset() : text;
}

std::string Color::reset()
{
    return "\033[0m";
}

int get_int(std::string msg) {
    int value;
    std::string input;

    while (true) {
        std::cout << msg;
        std::cin.clear();
        std::cin >> input;

        try {
            size_t pos;
            value = std::stoi(input, &pos);

            if (pos != input.length()) {
                throw std::invalid_argument("Неверный формат числа");
            }

            if (value < std::numeric_limits<int>::min() || value > std::numeric_limits<int>::max()) {
                throw std::out_of_range("Введенное число выходит за пределы типа int");
            }

            break;
        } catch (const std::invalid_argument &e) {
            std::cout << "Ошибка" << std::endl;
        } catch (const std::out_of_range &e) {
            std::cout << "Ошибка" << std::endl;
        }
    }

    return value;
}
