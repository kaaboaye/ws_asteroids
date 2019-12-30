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

//    std::vector<std::reference_wrapper<Player>> *Game::list_players() {
//        auto players_vec = new std::vector<std::reference_wrapper<Player>>;
//
//        for (auto it : players) {
//            auto& player = it.second;
//            players_vec->push_back(player);
//        }
//
//        return players_vec;
//    }

    static bi::managed_shared_memory init_memory_segment() {
        bi::shared_memory_object::remove("GameSegment");
        return bi::managed_shared_memory(bi::create_only, "GameSegment", 65536);
    }

    Game::Game() : memory_segment(init_memory_segment()),
                   players(*memory_segment.construct<players_map>("GamePlayersMap")(std::less<>(), players_allocator_t(
                           memory_segment.get_segment_manager()))) {
    }

    Game::~Game() {
        memory_segment.destroy<players_map>("GamePlayersMap");
        bi::shared_memory_object::remove("GameSegment");
    }

}
