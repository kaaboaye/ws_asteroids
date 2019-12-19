
#include <iostream>
#include "tcp_server.h"
#include "squential_id.h"

int main(int argc, char const *argv[]) {
    std::cout << "starting" << std::endl;
    bdsm_asteroidy::tcp_server::start(8080);
    std::cout << "finishing" << std::endl;
}