//
// Created by mieszkowaw on 13.12.19.
//

#ifndef BDSM_ASTEROIDS_MESSAGE_H
#define BDSM_ASTEROIDS_MESSAGE_H

#include <string>
#include "../game.h"

namespace bdsm_asteroidy::message {
    std::optional<std::string*> handle(Game &game, tcp_server::connection_t connection, const std::string &raw_message);
}


#endif //BDSM_ASTEROIDS_MESSAGE_H
