//
// Created by mieszkowaw on 13.12.19.
//

#ifndef BDSM_ASTEROIDS_MESSAGE_H
#define BDSM_ASTEROIDS_MESSAGE_H

#include <string>


std::optional<std::reference_wrapper<const std::string>> handle_message(const std::string &raw_message);


#endif //BDSM_ASTEROIDS_MESSAGE_H
