cmake_minimum_required(VERSION 3.10)

project(psockets_server)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_BUILD_TYPE Release)

add_executable(server server.cpp utils.hpp)

add_executable(client client.cpp client.cpp)