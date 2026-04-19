cmake_minimum_required(VERSION 4.1)
project(Snake_Game)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(Snake_Game main.cpp)

