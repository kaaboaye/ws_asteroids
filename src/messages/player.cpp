//
// Created by mieszkowaw on 14.12.19.
//

#include <iostream>
#include "player.h"
#include "../player.h"
#include "context.h"

using namespace bdsm_asteroidy;

inline json player_to_json(const Player &player) {
    return {
            {"id",       player.id},
            {"position", {
                                 {"x", player.position.get<0>()},
                                 {"y", player.position.get<1>()}
                         }},
            {"movement", {
                                 {"x", player.movement.get<0>()},
                                 {"y", player.movement.get<1>()},
                         }},
            {"rotation", player.rotation}
    };
}

inline void broadcast_player_update(Game &game, Player &player, sequence::val excluded_id = -1) {

    for (auto it : game.players) {
        std::cout << "player id " << it.second.id << std::endl;
    }

    auto message = json({
                                {"message", "player_updated"},
                                {"player",  player_to_json(player)}
                        }).dump() + "\n";

    for (auto it : game.players) {
        auto connected_player_id = it.second.id;
        auto connection = it.second.connection;

        if (connected_player_id == excluded_id) {
            continue;
        }

        tcp_server::send_message_to_connection(connection, message);
    }
}

json *message::player::create_player(message::context &ctx) {
    auto player = ctx.game.create_player(ctx.connection);

    broadcast_player_update(ctx.game, player, player.id);

    return new json({
                            {"message", "player_created"},
                            {"player",  player_to_json(player)}
                    });

}

nlohmann::json *message::player::list_players(bdsm_asteroidy::message::context &ctx) {
    json players;

    for (auto &it : ctx.game.players) {
        players.push_back(player_to_json(it.second));
    }

    return new json({
                            {"message", "listed_players"},
                            {"players", players}
    });
}


json *bdsm_asteroidy::message::player::get_player(bdsm_asteroidy::message::context &ctx) {
    auto player_id = ctx.payload.at("player_id").get<bdsm_asteroidy::sequence::val>();
    auto player = ctx.game.find_player(player_id);

    auto player_json = player.has_value() ? player_to_json(player.value()) : nlohmann::json();

    return new json({
                            {"message", "got_player"},
                            {"player",  player_json}
                    });

}

std::optional<json *> bdsm_asteroidy::message::player::move_player(bdsm_asteroidy::message::context &ctx) {
    auto player_id = ctx.payload.at("player_id").get<bdsm_asteroidy::sequence::val>();
    auto maybe_player = ctx.game.find_player(player_id);

    if (!maybe_player.has_value()) {
        return new json({
                                {"message", "player_moved"},
                                {"player",  nlohmann::json()}
                        });
    }

    auto &player = maybe_player.value().get();

    auto position = ctx.payload.at("position");
    auto movement = ctx.payload.at("movement");
    auto rotation = ctx.payload.at("rotation");

    player.position.set<0>(position.at("x").get<float>());
    player.position.set<1>(position.at("y").get<float>());

    player.movement.set<0>(movement.at("x").get<int8_t>());
    player.movement.set<1>(movement.at("y").get<int8_t>());

    player.rotation = rotation.get<float>();

    broadcast_player_update(ctx.game, player);

    return {};
}
