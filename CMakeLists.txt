cmake_minimum_required(VERSION 3.16)
project(bdsm_asteroids)

set(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_FLAGS -pthread)

include_directories(libs/websocketpp)
include_directories(libs/boost_1_69_0)
include_directories(libs/json/include)

add_executable(bdsm_asteroids src/main.cpp src/ws_server.cpp src/ws_server.h src/message.cpp src/message.h src/commands.cpp src/commands.h)
