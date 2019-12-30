//
// Created by mieszkowaw on 30.12.19.
//

#ifndef BDSM_ASTEROIDS_ASTEROID_H
#define BDSM_ASTEROIDS_ASTEROID_H


#include "squential_id.h"
#include <boost/geometry.hpp>

namespace bg = boost::geometry;

namespace bdsm_asteroidy {
    class asteroid {
    public:
        sequence::val id{};
        bg::model::point<float, 2, bg::cs::cartesian> position{};
        float rotation;

        asteroid(sequence::val id, bg::model::point<float, 2, bg::cs::cartesian> position, float rotation);
    };
}


#endif //BDSM_ASTEROIDS_ASTEROID_H
