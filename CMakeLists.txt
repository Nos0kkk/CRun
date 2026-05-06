cmake_minimum_required(VERSION 3.18)
project(crun VERSION 2.0 LANGUAGES CXX)

add_executable(crun ${CMAKE_SOURCE_DIR}/src/main.cpp)

install(TARGET crun RUNTIME DESTINATION bin) # for Linux
