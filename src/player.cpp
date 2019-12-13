//
// Created by mieszkowaw on 13.12.19.
//

#include <nlohmann/json.hpp>

#include "player.h"

using namespace bdsm_asteroidy;

using json = nlohmann::json;

player::player(tcp_server::connection_t connection)
        : id(sequential_id::create()), connection(connection) {
    json welcome_message = {
            {"message",      "player_created"},
            {"player",       {
                                     {"id",            id}
                             }},
            {"__internal__", {
                                     {"connection_id", connection}
                             }}
    };

    send_message(welcome_message.dump());
}

player::player() {
    id = 0;
    connection = 0;
}

void player::send_message(const std::string &message) const {
    tcp_server::send_message_to_connection(connection, message);
}
