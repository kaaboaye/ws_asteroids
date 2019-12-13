//
// Created by mieszkowaw on 13.12.19.
//

#include <netinet/in.h>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <sys/socket.h>
#include <sstream>
#include <iostream>
#include <boost/algorithm/string.hpp>

#include "tcp_server.h"
#include "message.h"
#include "player.h"
#include "game.h"

using namespace bdsm_asteroidy;

static void accept_connection(game &game_server, int server, struct sockaddr *addr, socklen_t *addrlen);

static void read_message(game &game_server, int connection);

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

    auto game_server = new game;
    accept_connection(*game_server, server_fd, (struct sockaddr *) &address, &addrlen);
    delete game_server;
}

void tcp_server::send_message_to_connection(tcp_server::connection_t connection, const std::string &message) {
    send(connection, message.c_str(), message.length(), 0);
}

static void accept_connection(game &game_server, int server, struct sockaddr *addr, socklen_t *addrlen) {
    int connection;

    if ((connection = accept(server, addr, addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    player new_player(connection);

    auto f = fork();

    if (f < 0) {
        perror("fork jebnol");
        exit(EXIT_FAILURE);
    }

    if (f == 0) {
        game_server.players[new_player.id] = new_player;
        read_message(game_server, connection);
        exit(0);
    }

    // tak to się kończy jak erlangowiec ma pisać cpp
    accept_connection(game_server, server, addr, addrlen);
}

static void read_message(game &game_server, int connection) {
    char buffer[2000] = {0};
    read(connection, buffer, sizeof(buffer));

    std::string str = buffer;
    boost::trim_right(str);

    std::cout << "Received: " << str << std::endl;

    auto resp = message::handle(str);


    if (str == "exit") {
        std::cout << "Disconnecting" << std::endl;
        shutdown(connection, 2);
        return;
    }

    read_message(game_server, connection);
}
