#include <iostream>
#include "database.hpp"
#include "ui.h"
#include "models.h"


int main() {
    setlocale(LC_ALL, "rus");
    Database<User> user_database {"users.csv" };
    Database<Artist> artist_database {"artists.csv" };
    Logger logger;
    Authentication auth_service { user_database };
    Color color {true};
    UI ui { user_database, artist_database, logger, color };
    ui.entry_point(auth_service);
}
