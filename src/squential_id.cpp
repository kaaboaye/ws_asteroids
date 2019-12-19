//
// Created by mieszkowaw on 13.12.19.
//

#include <atomic>
#include "squential_id.h"

using namespace bdsm_asteroidy;

sequence::val sequence::next() {
    return ++counter;
}
