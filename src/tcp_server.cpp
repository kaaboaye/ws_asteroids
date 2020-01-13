//
// Created by mieszkowaw on 13.12.19.
//

#include <netinet/in.h>
#include <cstdlib>
#include <unistd.h>
#include <sys/socket.h>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <sys/shm.h>
#include <malloc.h>
#include <cerrno>
#include <error.h>

#include "tcp_server.h"
#include "messages/message.h"
#include "player.h"
#include "game.h"

using namespace bdsm_asteroidy;

static void accept_connection(int game_server_seg, int server, struct sockaddr *addr, socklen_t *addrlen);

static void read_message(Game &game_server, int connection);

void bdsm_asteroidy::tcp_server::start(int port) {
    int server_fd;
    struct sockaddr_in address{};
    int opt = 1;
    socklen_t addrlen = sizeof(address);

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                   &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *) &address,
             sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }


    int game_server_seg;
    if ((game_server_seg = shmget(IPC_PRIVATE, sizeof(Game), IPC_CREAT | 0666)) < 0) {
        perror("smget returned -1\n");
        error(-1, errno, " ");
        exit(-1);
    }

    Game *game_server;

    if ((game_server = (Game *) shmat(game_server_seg, nullptr, 0)) == (Game *) -1) {
        perror("Process shmat returned NULL\n");
        error(-1, errno, " ");
    }

    new(game_server) Game();

    accept_connection(game_server_seg, server_fd, (struct sockaddr *) &address, &addrlen);
}

void tcp_server::send_message_to_connection(tcp_server::connection_t connection, const std::string &message) {
    try {
        std::cout << "2134234234" << std::endl;
        send(connection, message.c_str(), message.length(), 0);
    } catch (...) {
        std::cout << "xddsfdsdf" << std::endl;
    }
}

static void accept_connection(int game_server_seg, int server, struct sockaddr *addr, socklen_t *addrlen) {
    int connection;


    if ((connection = accept(server, addr, addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    auto f = fork();

    if (f < 0) {
        perror("fork jebnol");
        exit(EXIT_FAILURE);
    }

    if (f == 0) {
        Game *game_server;

        if ((game_server = (Game *) shmat(game_server_seg, nullptr, 0)) == (Game *) -1) {
            perror("Process shmat returned NULL\n");
            error(-1, errno, " ");
        }

        static std::string welcome = "{\"message\":\"welcome\"}\n";
        send(connection, welcome.c_str(), welcome.size(), 0);
        read_message(*game_server, connection);
        exit(0);
    }

    // tak to się kończy jak erlangowiec ma pisać cpp
    accept_connection(game_server_seg, server, addr, addrlen);
}

static void read_message(Game &game_server, int connection) {
    char buffer[1024] = {0};
    read(connection, buffer, sizeof(buffer));

    std::string str = buffer;
    boost::trim_right(str);

    std::vector<std::string> commands;

    boost::algorithm::split(commands, str, boost::algorithm::is_any_of("\n"));

    for (auto &command : commands) {
        std::cout << "Received: " << command << std::endl;

        if (command == "exit") {
            std::cout << "Disconnecting" << std::endl;
            shutdown(connection, 2);
            return;
        }

        auto resp = message::handle(game_server, connection, command);

        if (resp.has_value()) {
            auto resp_str = resp.value();
            send(connection, resp_str->c_str(), resp_str->size(), 0);
            delete resp_str;
        }
    }

    read_message(game_server, connection);
}
