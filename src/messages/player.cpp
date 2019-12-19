//
// Created by mieszkowaw on 14.12.19.
//

#include "player.h"
#include "../player.h"
#include "context.h"

inline json player_to_json(const bdsm_asteroidy::Player &player) {
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

json *bdsm_asteroidy::message::player::create_player(message::context &ctx) {
    auto player = ctx.game.create_player(ctx.connection);

    return new json({
                            {"message", "player_created"},
                            {"player",  player_to_json(player)}
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

    auto *all_players = ctx.game.list_players();

    auto message = json({
                                {"message", "player_moved"},
                                {"player",  player_to_json(player)}
                        }).dump();

    for (auto it : *all_players) {
        auto _player = it.get();
        tcp_server::send_message_to_connection(_player.connection, message);
    }

    return {};
}
