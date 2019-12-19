//
// Created by mieszkowaw on 13.12.19.
//

#include <nlohmann/json.hpp>

#include "player.h"

using namespace bdsm_asteroidy;

using json = nlohmann::json;

Player::Player(sequence::val id, tcp_server::connection_t connection)
        : id(id), connection(connection) {
    position.set<0>(0);
    position.set<1>(0);

    movement.set<0>(0);
    movement.set<1>(0);

    rotation = 0;
}

Player::Player() {
    id = 0;
    connection = 0;

    position.set<0>(0);
    position.set<1>(0);

    movement.set<0>(0);
    movement.set<1>(0);

    rotation = 0;
}

void Player::send_message(const std::string &message) const {
    tcp_server::send_message_to_connection(connection, message);
}
