//
// Created by Renat Yakublevich on 20.11.23.
//

#include "controllers.h"

Entities<Artist> search_by_year(Entities<Artist> artists, int left_range, int right_range) {
    Artist* new_artists = new Artist[MAX_COUNT_ENTITIES];
    int index = 0;

    for (int i = 0; i < artists.length; ++i) {
        if (artists.entities[i].get_year() >= left_range && artists.entities[i].get_year() <= right_range) {
            new_artists[index] = artists.entities[i];
            index++;
        }
    }
    return {new_artists, index};
}

Entities<Artist> get_instrument_tier_list(Entities<Artist>* artists, std::string instruemnt) {
    Artist* new_artists = new Artist[3];
    int index = 0;
    sort_by_place(artists);
    for (int i = 0; i < artists->length; ++i) {
        if (index == 2) break;
        if (artists->entities[i].get_instrument() == instruemnt) {
            new_artists[index] = artists->entities[i];
            index++;
        }
    }
    return {new_artists, index};
}

Entities<std::string> get_all_instruments(Entities<Artist> artists) {
    std::string* instruments = new string[MAX_COUNT_ENTITIES];
    int index = 0;

    for (int i = 0; i < artists.length; ++i) {
        if (!str_exists(artists.entities[i].get_instrument(), instruments, index)) {
            instruments[index] = artists.entities[i].get_instrument();
            index++;
        }
    }
    return {instruments, index};
}