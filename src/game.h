//
// Created by mieszkowaw on 13.12.19.
//

#ifndef BDSM_ASTEROIDS_GAME_H
#define BDSM_ASTEROIDS_GAME_H

#include <tbb/concurrent_unordered_map.h>

#include "squential_id.h"
#include "player.h"

using namespace bdsm_asteroidy;

class game {
public:
    tbb::concurrent_unordered_map<sequential_id::t, player> players;
};


#endif //BDSM_ASTEROIDS_GAME_H
