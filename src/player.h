//
// Created by mieszkowaw on 13.12.19.
//

#ifndef BDSM_ASTEROIDS_PLAYER_H
#define BDSM_ASTEROIDS_PLAYER_H


#include <string>
#include "tcp_server.h"
#include "squential_id.h"

namespace bdsm_asteroidy {
    class player {
    public:
        sequential_id::t id{};
        tcp_server::connection_t connection{};

        player();
        explicit player(tcp_server::connection_t connection);

        inline void send_message(const std::string& message) const;
    };
}


#endif //BDSM_ASTEROIDS_PLAYER_H
