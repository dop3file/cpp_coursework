#include "ui.h"


void UI::entry_point(Authentication auth_service) {
    logger.log("Запуск программы");
    while (1) {
        std::cout << color.get_colorfull_text("Привет!\nЭто программа справочник по музыкальному конкурсу", color.GREEN) << std::endl;
        std::cout << "1. Войти" << std::endl << "2. Зарегистрироваться" << std::endl << "3. Выйти" << std::endl;

        Entities<User> users = user_database.select_all()->select_all();

        std::string login;
        std::string password;
        User* current_user;

        std::string user_choosen;
        std::cin >> user_choosen;

        if (user_choosen[0] == '1' || user_choosen[0] == '2') {
            std::cout << "Введите логин: ";
            std::cin >> login;
            std::cout << "Введите пароль: ";
            std::cin >> password;
        }
        if (user_choosen[0] == '1') {
            current_user = auth_service.authenticate(login, password);
            if (current_user == nullptr) {
                std::cout << color.get_colorfull_text("Неверные данные!", color.RED) << std::endl;
            }
            else {
                std::cout << color.get_colorfull_text("Вы успешно авторизовались!", color.GREEN) << std::endl;
                main_screen_router(current_user);
            }
        }
        else if (user_choosen[0] == '2') {
            if (user_exists(login, users)) {
                std::cout << "Пользователь с таким ником существует!" << std::endl;
                continue;
            }
            auth_service.registration(login, auth_service.hash_password(password));
            std::cout << "Вы успешно зарегистрировались!" << std::endl;
        }
        else if (user_choosen[0] == '3') {
            std::cout << "Пока!";
            return;
        }
    }
}

void UI::main_screen_router(User* user) {
    logger.log("Пользователь вошел под ником " + user->get_login());
    std::cout << color.get_italic_text(user->get_description());
    if (user->is_admin()) admin_main_screen(user);
    else user_main_screen(user);
}

void UI::search_by_year_screen(Collection <Artist> collection) {
    int left_range;
    int right_range;
    std::cout << "Введите левый диапозон возвраста: ";
    std::cin >> left_range;
    std::cout << "Введите правый диапозон возвраста: ";
    std::cin >> right_range;

    Entities<Artist> artists = collection.select_all();
    artists = search_by_year(artists, left_range, right_range);
    get_all_entities_screen(artists);
}

void UI::get_tier_list_screen(Entities<Artist>* artists) {
    Entities<std::string> instruments = get_all_instruments(*artists);
    for (int i = 0; i < instruments.length; ++i) {
        Entities<Artist> tmp = get_instrument_tier_list(artists, instruments.entities[i]);
        std::cout << "Топ 3 по инструменту: " << instruments.entities[i] << std::endl;
        get_all_entities_screen(tmp);
    }
}

void UI::user_main_screen(User* user) {
    int user_choosen;
    while(1) {
        Collection<Artist>* collection = artist_database.select_all();
        Entities<Artist> artists = collection->select_all();
        output_menu_options(user);
        std::cout << "Выберите пункт меню: ";
        std::cin >> user_choosen;
        switch (user_choosen) {
            case 1:
                get_all_entities_screen(collection->select_all());
                break;
            case 2:
                get_tier_list_screen(&artists);
                break;
            case 3:
                search_by_year_screen(*collection);
                break;
            case 4:
                delete collection;
                return;
            default:
                std::cout << "Такого варианта нет" << std::endl;
                break;
        }
    }
}

void UI::add_user_screen(Collection<User>* collection) {
    Authentication auth = {this->user_database};
    std::string login;
    std::string password;
    std::string is_admin;
    std::cin.clear();
    std::cout << "Введите логин: \n";
    std::cin >> login;
    std::cout << "Введите пароль: ";
    std::cin >> password;
    std::cout << "Введите + если пользователь админ и - если нет: ";
    std::cin >> is_admin;
    logger.log("Админ добавил пользователя под ником " + login);
    collection->insert(
            {login, auth.hash_password(password), is_admin == "+"}
    );
}


void UI::admin_user_crud_screen() {
    int user_choosen;
    Collection<User>* user_collection = user_database.select_all();
    Entities<User> users = user_collection->select_all();
    while(1) {
        std::cout << "1. Добавление пользователя\n2. Удаление пользователя\n3. Просмотр пользователей\n4. Сохранить\n5. Откат изменений\n6. Выйти\nВыберите пункт меню: ";
        std::cin >> user_choosen;
        switch (user_choosen) {
            case 1:
                add_user_screen(user_collection);
                std::cout << "Пользователь успешно добавлен!" << std::endl;
                break;
            case 2: {
                std::string login;
                std::cout << "Введите логин пользователя: ";
                std::cin >> login;
                User user = {login};
                user_collection->del(user);
                logger.log("Админ удалил пользователя под ником " + login);
                std::cout << "Пользователь удален!" << std::endl;
                break;
            }
            case 3:
                get_all_entities_screen(user_collection->select_all());
                break;
            case 4: {
                logger.log("Админ сохранил изменения");
                user_database.clear();
                users = user_collection->select_all();
                for (int i = 0; i < users.length; ++i) {
                    user_database.insert(users.entities[i]);
                }
                std::cout << "Изменения успешно сохранены!" << std::endl;
                break;
            }
            case 5:
                user_collection = user_database.select_all();
                std::cout << "Действия отменены!" << std::endl;
                break;
            case 6:
                delete user_collection;
                return;
            default:
                std::cout << "Такого пункта нет" << std::endl;
                break;
        }
    }
}

void UI::add_artist_screen(Collection<Artist> collection) {
    std::string surname;
    int year;
    std::string country;
    std::string instrument;
    int place;
    std::cin.clear();
    std::cout << "Введите фамилию участника: ";
    std::cin >> surname;
    year = get_int("Введите возвраст участника: ");
    std::cout << "Введите страну участника: ";
    std::cin >> country;
    std::cout << "Введите инструмент участника: ";
    std::cin >> instrument;
    place = get_int("Введите место занятое участником: ");
    collection.insert(
            {surname, year, country, instrument, place}
    );
}

void UI::admin_artist_crud_screen() {
    int user_choosen;
    Collection<Artist>* collection = artist_database.select_all();
    while(1) {
        std::cout << "1. Добавление участника\n2. Удаление участника\n3. Просмотр участников\n4. Сохранить\n5. Откат изменений\n6. Выйти\nВыберите пункт меню: ";
        std::cin >> user_choosen;
        switch (user_choosen) {
            case 1:
                add_artist_screen(*collection);
                std::cout << "Участник успешно добавлен!" << std::endl;
                break;
            case 2: {
                std::string surname;
                std::cout << "Введите фамилию участника: ";
                std::cin >> surname;
                Artist tmp = Artist(surname);
                collection->del(tmp);
                break;
            }
            case 3:
                get_all_entities_screen(collection->select_all());
                break;
            case 4: {
                artist_database.clear();
                Entities<Artist> artists = collection->select_all();
                for (int i = 0; i < artists.length; ++i) {
                    artist_database.insert(artists.entities[i]);
                }
                std::cout << "Изменения успешно сохранены!" << std::endl;
                break;
            }
            case 5:
                collection = artist_database.select_all();
                std::cout << "Действия отменены!" << std::endl;
                break;
            case 6:
                delete collection;
                return;
            default:
                std::cout << "Такого пункта нет" << std::endl;
                break;
        }
    }
}

void UI::output_menu_options(User* user) {
    Entities<string> menu_options = user->get_menu_options();
    for (int i = 0; i < menu_options.length; ++i) {
        std::cout << i + 1 << ". " << color.get_colorfull_text(color.get_bold_text(menu_options.entities[i]), color.BLUE) << std::endl;
    }
}

void UI::admin_main_screen(User* user) {
    int user_choosen;
    while(1) {
        std::cout << "У вас есть привилегии администратора" << std::endl;
        output_menu_options(user);
        std::cout << "Выберите пункт меню: ";
        std::cin >> user_choosen;
        switch (user_choosen) {
            case 1:
                admin_user_crud_screen();
                break;
            case 2:
                admin_artist_crud_screen();
                break;
            case 3:
                return;
            default:
                std::cout << "Такого варианта нет" << std::endl;
                break;
        }
    }
}

UI::UI(Database<User> user_database, Database<Artist> artist_database, Logger logger, Color color) : user_database(user_database), artist_database(artist_database), logger(logger), color(color) {};



