cmake_minimum_required(VERSION 3.16)
project(bdsm_asteroids)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-lrt -ltbb -lpthread")

include_directories(libs/boost_1_69_0)
include_directories(libs/json/include)
include_directories(libs/tbb/src)

add_executable(bdsm_asteroids
        src/main.cpp
        src/messages/message.cpp
        src/messages/message.h
        src/commands.cpp
        src/commands.h
        src/tcp_server.cpp
        src/tcp_server.h
        src/squential_id.cpp
        src/squential_id.h
        src/player.cpp
        src/player.h
        src/game.cpp
        src/game.h
        src/messages/player.cpp
        src/messages/player.h
        src/messages/context.h
        src/asteroid.cpp src/asteroid.h)

