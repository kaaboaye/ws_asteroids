//
// Created by mieszkowaw on 13.12.19.
//

#ifndef BDSM_ASTEROIDS_WS_SERVER_H
#define BDSM_ASTEROIDS_WS_SERVER_H

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

typedef websocketpp::server<websocketpp::config::asio> ws_server;

void run_ws_server();


#endif //BDSM_ASTEROIDS_WS_SERVER_H
