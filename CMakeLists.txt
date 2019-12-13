cmake_minimum_required(VERSION 3.16)
project(bdsm_asteroids)

set(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_FLAGS -ltbb)

include_directories(libs/boost_1_69_0)
include_directories(libs/json/include)
include_directories(libs/tbb/src)

add_executable(bdsm_asteroids src/main.cpp src/message.cpp src/message.h src/commands.cpp src/commands.h src/tcp_server.cpp src/tcp_server.h src/squential_id.cpp src/squential_id.h src/player.cpp src/player.h src/game.cpp src/game.h)
