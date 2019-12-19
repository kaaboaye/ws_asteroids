//
// Created by mieszkowaw on 13.12.19.
//

#include "game.h"
#include "player.h"

namespace bdsm_asteroidy {

    Player Game::create_player(tcp_server::connection_t connection) {
        Player player(id_seq.next(), connection);
        players[player.id] = player;
        return player;
    }

    std::optional<std::reference_wrapper<Player>> Game::find_player(sequence::val player_id) {
        auto it = players.find(player_id);
        if (it == players.end()) {
            return std::nullopt;
        }
        return it->second;
    }

    std::vector<std::reference_wrapper<Player>>* Game::list_players() {
        auto players_vec = new std::vector<std::reference_wrapper<Player>>;

        for (auto it : players) {
            auto& player = it.second;
            players_vec->push_back(player);
        }

        return players_vec;
    }

}
