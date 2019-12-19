//
// Created by mieszkowaw on 13.12.19.
//

#ifndef BDSM_ASTEROIDS_SQUENTIAL_ID_H
#define BDSM_ASTEROIDS_SQUENTIAL_ID_H

#include <cstdint>
#include <atomic>

namespace bdsm_asteroidy {
    class sequence {
    public:
        typedef uint64_t val;
        std::atomic<val> counter = 0;
        val next();
    };
}


#endif //BDSM_ASTEROIDS_SQUENTIAL_ID_H
