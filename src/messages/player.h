//
// Created by mieszkowaw on 14.12.19.
//

#ifndef BDSM_ASTEROIDS_MESSAGE_PLAYER_H
#define BDSM_ASTEROIDS_MESSAGE_PLAYER_H

#include <nlohmann/json.hpp>

namespace bdsm_asteroidy::message {
    struct context;
}

namespace bdsm_asteroidy::message::player {
    nlohmann::json* create_player(bdsm_asteroidy::message::context &ctx);
    nlohmann::json* list_players(bdsm_asteroidy::message::context &ctx);
    nlohmann::json* get_player(bdsm_asteroidy::message::context &ctx);
    std::optional<nlohmann::json*> move_player(bdsm_asteroidy::message::context &ctx);
}

#endif //BDSM_ASTEROIDS_PLAYER_H
