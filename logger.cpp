//
// Created by Renat Yakublevich on 18.11.23.
//

#include "logger.h"


std::string Logger::read() {
    std::ifstream file(file_name);
    std::string result = "";
    if (file.is_open()) {
        std::string line;

        while (std::getline(file, line)) {
            result += line + "\n";
        }

        file.close();
    }
    return result;
}

void Logger::log(std::string record) {
    std::ofstream file(file_name, std::ios::out | std::ios::app);

    if (file.is_open()) {
        file << get_date() << " " << record << std::endl;
    }
    file.close();
}
