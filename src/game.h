//
// Created by mieszkowaw on 13.12.19.
//

#ifndef BDSM_ASTEROIDS_GAME_H
#define BDSM_ASTEROIDS_GAME_H


#include <tbb/concurrent_unordered_map.h>

#include "squential_id.h"
#include "tcp_server.h"

namespace bdsm_asteroidy {
    class Player;

    class Game {
    public:
        Player create_player(tcp_server::connection_t connection);
        std::optional<std::reference_wrapper<Player>> find_player(sequence::val player_id);
        std::vector<std::reference_wrapper<Player>>* list_players();

    private:
        sequence id_seq;
        tbb::concurrent_unordered_map<sequence::val, Player> players;
    };
}



#endif //BDSM_ASTEROIDS_GAME_H
