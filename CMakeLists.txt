cmake_minimum_required(VERSION 3.17)
project(QPP)

set(CMAKE_CXX_STANDARD 14)

add_executable(QPP main.cpp)
target_link_libraries(QPP m)