//
// Created by Renat Yakublevich on 20.11.23.
//

#ifndef KURS_CONTROLLERS_H
#define KURS_CONTROLLERS_H

#include "models.h"
#include "misc.h"

Entities<Artist> search_by_year(Entities<Artist> artists, int left_range, int right_range);

Entities<std::string> get_all_instruments(Entities<Artist> artists);

Entities<Artist> get_instrument_tier_list(Entities<Artist>* artists, std::string instruemnt);


#endif //KURS_CONTROLLERS_H
