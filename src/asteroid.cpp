//
// Created by mieszkowaw on 30.12.19.
//

#include "asteroid.h"

bdsm_asteroidy::asteroid::asteroid(sequence::val id, bg::model::point<float, 2, bg::cs::cartesian> position,
                                   float rotation) :
        id(id), position(position), rotation(rotation) {
}
