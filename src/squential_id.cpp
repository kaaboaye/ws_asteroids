//
// Created by mieszkowaw on 13.12.19.
//

#include <atomic>
#include "squential_id.h"

using namespace bdsm_asteroidy;


sequential_id::t sequential_id::create() {
static std::atomic<sequential_id::t> counter = 0;
    return ++counter;
}
