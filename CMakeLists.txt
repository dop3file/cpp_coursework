cmake_minimum_required(VERSION 3.25)
project(kurs)

set(CMAKE_CXX_STANDARD 17)

add_executable(curs main.cpp models.cpp models.h database.hpp ui.cpp ui.h collection.h auth.cpp auth.h misc.cpp misc.h logger.cpp logger.h sha256.h sha256.cpp database.cpp collection.cpp controllers.cpp controllers.h
        auth.cpp)