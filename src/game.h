//
// Created by mieszkowaw on 13.12.19.
//

#ifndef BDSM_ASTEROIDS_GAME_H
#define BDSM_ASTEROIDS_GAME_H

#include <functional>

#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/map.hpp>
#include <boost/interprocess/containers/vector.hpp>

#include <tbb/concurrent_unordered_map.h>

#include "squential_id.h"
#include "tcp_server.h"

namespace bi = boost::interprocess;

namespace bdsm_asteroidy {
    class Player;

    class Game {
    public:
        Game();
        ~Game();

        Player create_player(tcp_server::connection_t connection);

        std::optional<std::reference_wrapper<Player>> find_player(sequence::val player_id);

//        std::vector<std::reference_wrapper<Player>> *list_players();

//    private:
        bi::managed_shared_memory memory_segment;

        typedef bi::allocator<std::pair<const sequence::val, Player>, bi::managed_shared_memory::segment_manager>
                players_allocator_t;

        typedef bi::map<sequence::val, Player, std::less<>, players_allocator_t> players_map;

        sequence id_seq;
//        tbb::concurrent_unordered_map<sequence::val, Player> players;
        players_map& players;
    };
}


#endif //BDSM_ASTEROIDS_GAME_H
