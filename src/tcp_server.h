//
// Created by mieszkowaw on 13.12.19.
//

#ifndef BDSM_ASTEROIDS_TCP_SERVER_H
#define BDSM_ASTEROIDS_TCP_SERVER_H


namespace bdsm_asteroidy::tcp_server {
    typedef int connection_t;

    void start(int port);

    void send_message_to_connection(connection_t connection, const std::string& message);
}

#endif //BDSM_ASTEROIDS_TCP_SERVER_H
