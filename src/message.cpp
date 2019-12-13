//
// Created by mieszkowaw on 13.12.19.
//

#include <iostream>

#include <nlohmann/json.hpp>

#include "message.h"
#include "commands.h"

using json = nlohmann::json;

std::string bdsm_asteroidy::message::handle(const std::string &raw_message) {
    try {
        auto msg = json::parse(raw_message);

        std::cout << msg.dump(4) << std::endl;

        auto command = msg.at("message").get<std::string>();

        std::cout << "CMD: " << command << std::endl;

        command::t parsed_cmd = command::from_string(command);

        return command::to_string(parsed_cmd) + "\n";
    } catch (...) {
        std::cout << "Incorrect message received" << std::endl
                  << raw_message << std::endl;

        return "{\"message\":\"error\",\"code\":\"bad_format\"}\n";
    }
}
