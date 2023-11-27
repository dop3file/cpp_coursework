//
// Created by Renat Yakublevich on 18.11.23.
//

#ifndef KURS_MISC_H
#define KURS_MISC_H

#include "models.h"
#include <iostream>

bool user_exists(std::string login, Entities<User> users);

bool str_exists(std::string str, std::string* arr, int length);

void sort_by_place(Entities<Artist>* artists);

std::string get_date();

class Color {
public:
    std::string get_colorfull_text(std::string text, int color_code);

    std::string get_italic_text(std::string text);

    std::string get_bold_text(std::string text);

    std::string reset();

    Color(bool using_color) : using_color(using_color) {};

    const int RED = 31;
    const int GREEN = 32;
    const int BLUE = 34;
    const int BLACK = 30;

    bool using_color;
};

int get_int(std::string msg);



#endif //KURS_MISC_H
