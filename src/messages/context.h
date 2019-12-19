//
// Created by mieszkowaw on 14.12.19.
//

#ifndef BDSM_ASTEROIDS_CONTEXT_H
#define BDSM_ASTEROIDS_CONTEXT_H

#include <nlohmann/json.hpp>
#include "../game.h"
#include "../tcp_server.h"

using json = nlohmann::json;


namespace bdsm_asteroidy::message {
    struct context {
        Game &game;
        json &payload;
        tcp_server::connection_t connection;
    };
}


#endif //BDSM_ASTEROIDS_CONTEXT_H
