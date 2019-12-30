//
// Created by mieszkowaw on 13.12.19.
//

#ifndef BDSM_ASTEROIDS_PLAYER_H
#define BDSM_ASTEROIDS_PLAYER_H


#include <string>
#include "tcp_server.h"
#include "squential_id.h"
#include <boost/geometry.hpp>

namespace bg = boost::geometry;

namespace bdsm_asteroidy {
    class Player {
    public:
        sequence::val id{};
        tcp_server::connection_t connection{};
        bg::model::point<float, 2, bg::cs::cartesian> position{};
        bg::model::point<int8_t, 2, bg::cs::cartesian> movement{};
        float rotation;

        Player();
        Player(sequence::val id, tcp_server::connection_t connection);

        inline void send_message(const std::string& message) const;
    };
}


#endif //BDSM_ASTEROIDS_PLAYER_H
