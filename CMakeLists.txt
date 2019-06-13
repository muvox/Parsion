cmake_minimum_required(VERSION 3.14)
project(Parsion)

set(CMAKE_CXX_STANDARD 14)

set (CMAKE_CXX_FLAGS "-lmingw32 -static-libgcc -static-libstdc++")

set(CMAKE_MODULE_PATH "C:/Dev/CPP/CMake/Modules")

set(SDL2_PATH "C:/Dev/CPP/SDL2-2.0.9/x86_64-w64-mingw32")

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIR})

add_executable(Parsion main.cpp Screen.cpp Screen.h Particle.cpp Particle.h Swarm.cpp Swarm.h)

target_link_libraries(Parsion
        ${SDL2MAIN_LIBRARY}
        ${SDL2_LIBRARY})