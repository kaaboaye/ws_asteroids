//
// Created by mieszkowaw on 13.12.19.
//

#include <iostream>

#include <nlohmann/json.hpp>

#include "message.h"
#include "commands.h"

using json = nlohmann::json;

std::optional<std::reference_wrapper<const std::string>> handle_message(const std::string &raw_message) {
    try {
        auto msg = json::parse(raw_message);

        std::cout << msg.dump(4) << std::endl;

        auto command = msg.at("message").get<std::string>();

        std::cout << "CMD: " << command << std::endl;

        command::t parsed_cmd = command::from_string(command);

        auto& str_cmd = command::to_string(parsed_cmd);
        return std::optional<std::reference_wrapper<const std::string>>(str_cmd);
    } catch (...) {
        std::cout << "Incorrect message received" << std::endl
                  << raw_message << std::endl;

        return {};
    }
}
