//
// Created by mieszkowaw on 13.12.19.
//

#ifndef BDSM_ASTEROIDS_COMMANDS_H
#define BDSM_ASTEROIDS_COMMANDS_H

#include <string>

namespace command {
    enum t {
        unknown,
        create_player,
        move_player,
        fire,
    };

    t from_string(const std::string &command);

    const std::string &to_string(t command);
}

#endif //BDSM_ASTEROIDS_COMMANDS_H
