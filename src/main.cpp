
#include <iostream>
#include "tcp_server.h"
#include "squential_id.h"

int main(int argc, char const *argv[]) {
    std::cout << "starting" << bdsm_asteroidy::sequential_id::create() << bdsm_asteroidy::sequential_id::create() << std::endl;
    bdsm_asteroidy::tcp_server::start(8080);
    std::cout << "finishing" << std::endl;
}