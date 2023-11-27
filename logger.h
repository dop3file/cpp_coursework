//
// Created by Renat Yakublevich on 18.11.23.
//

#ifndef KURS_LOGGER_H
#define KURS_LOGGER_H

#include <iostream>
#include <fstream>

#include "misc.h"

class Logger {
public:
    void log(std::string record);
    std::string read();
private:
    const std::string file_name = "log.log";
};


#endif //KURS_LOGGER_H
