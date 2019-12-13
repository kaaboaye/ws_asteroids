//
// Created by mieszkowaw on 13.12.19.
//

#include <iostream>

#include "ws_server.h"
#include "message.h"

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

typedef ws_server::message_ptr message_ptr;

static void on_message(ws_server *s, const websocketpp::connection_hdl &hdl, const message_ptr &msg) {
    hdl.lock();

    auto resp = handle_message(msg->get_payload());

    // check for a special command to instruct the server to stop listening so
    // it can be cleanly exited.
//    if (msg->get_payload() == "stop-listening") {
//        s->stop_listening();
//        return;
//    }

    try {
        if (resp.has_value()) {
            s->send(hdl, resp.value(), msg->get_opcode());
        } else {
            s->send(hdl, R"({"error":"Internal Server Error")", msg->get_opcode());
        }
    } catch (websocketpp::exception const &e) {
        std::cout << "Echo failed because: "
                  << "(" << e.what() << ")" << std::endl;
    }
}

void run_ws_server() {
    ws_server server;

    try {
        server.set_access_channels(websocketpp::log::alevel::all);
        server.clear_access_channels(websocketpp::log::alevel::frame_payload);

        // Initialize Asio
        server.init_asio();

        // Register our message handler
        server.set_message_handler(bind(&on_message, &server, ::_1, ::_2));

        // Listen on port 9002
        server.listen(9002);

        // Start the server accept loop
        server.start_accept();

        std::cout << "Server is running at port 9002" << std::endl;

        // Start the ASIO io_service run loop
        server.run();

    } catch (websocketpp::exception const &e) {
        std::cout << e.what() << std::endl;
    } catch (...) {
        std::cout << "other exception" << std::endl;
    }
}
