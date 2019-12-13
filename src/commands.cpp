//
// Created by mieszkowaw on 13.12.19.
//

#include <unordered_map>
#include "commands.h"

static std::unordered_map<std::string, command::t> str_to_command = { // NOLINT(cert-err58-cpp)
        {"create_player", command::create_player},
        {"move_player", command::move_player},
        {"fire", command::fire}
};

command::t command::from_string(const std::string &command) {
    auto cmd = str_to_command.find(command);

    if (cmd == str_to_command.end()) {
        return command::unknown;
    }

    return cmd->second;
}

static std::string command_to_str[] = {
        "unknown",
        "create_player",
        "move_player",
        "fire",
};

const std::string &command::to_string(command::t command) {
    return command_to_str[command];
}
