//
// Created by mieszkowaw on 13.12.19.
//

#include <iostream>

#include <nlohmann/json.hpp>

#include "message.h"
#include "../commands.h"
#include "context.h"
#include "player.h"

using json = nlohmann::json;
using namespace bdsm_asteroidy;

std::optional<json*> handle_command(Game& game, command::t command, json& payload, tcp_server::connection_t connection) {
    message::context ctx = {game, payload, connection};

    switch (command) {
        case command::create_player:
            return message::player::create_player(ctx);
        case command::get_player:
            return message::player::get_player(ctx);
        case command::move_player:
            return message::player::move_player(ctx);
        case command::fire:
            return new json({{"message", "player_fired"}, {"error", "not_implemented"}});
        case command::unknown:
            return new json({{"message", "unknown_command"}});

    }
}

std::optional<std::string*> message::handle(Game &Game, tcp_server::connection_t connection,
                                const std::string &raw_message) {
    try {
        auto msg = json::parse(raw_message);
        auto command_str = msg.at("message").get<std::string>();
        auto command = command::from_string(command_str);

        std::cout << "CMD: " << command::to_string(command) << std::endl;

        auto resp = handle_command(Game, command, msg, connection);

        if (resp.has_value()) {
            auto resp_str = new std::string(resp.value()->dump() + "\n");
            delete resp.value();
            return resp_str;
        }
    } catch (...) {
        std::cout << "Incorrect message received" << std::endl
                  << raw_message << std::endl;

        return new std::string("{\"message\":\"error\",\"code\":\"bad_format\"}\n");
    }
}
