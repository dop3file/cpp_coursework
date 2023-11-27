#ifndef KURS_UI_H
#define KURS_UI_H

#define MAX_LEN_STRING 1024

#include "database.hpp"
#include "auth.h"
#include "misc.h"
#include "logger.h"
#include "models.h"
#include "controllers.h"

#include <iostream>

class UI {
public:
    void entry_point(Authentication auth_service);

    void main_screen_router(User* user);

    void user_main_screen(User* user);

    template<typename T>
    void get_all_entities_screen(Entities<T> entities) {
        std::cout << "Количество - " << entities.length << std::endl;
        std::cout << T::get_header() << std::endl;
        entities.sort();
        for (int i = 0; i < entities.length; i++) {
            entities.entities[i].output_table_description(i + 1);
        }
        if (entities.length == 0) std::cout << "Записей нет!" << std::endl;
        std::cout << T::get_footer() << std::endl;
    }

    void add_user_screen(Collection<User>* user_colleciton);

    void admin_user_crud_screen();

    void admin_artist_crud_screen();

    void admin_main_screen(User* user);

    void add_artist_screen(Collection<Artist> collection);

    void get_all_artists_screen(Entities<Artist> artists);

    void get_tier_list_screen(Entities<Artist>* artists);

    void search_by_year_screen(Collection <Artist> collection);

    void output_menu_options(User* user);

    UI(Database<User> user_database, Database<Artist> artist_database, Logger logger, Color color);

private:
    Database<User> user_database;
    Database<Artist> artist_database;
    Logger logger;
    Color color;
};

#endif //KURS_UI_H
