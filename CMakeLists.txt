cmake_minimum_required(VERSION 3.20)
project(pacman)

find_package(SFML 2.5 REQUIRED COMPONENTS graphics window system)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(Logic)

set(PACMAN_SOURCES
        main.cpp
        Representation/Game.cpp
        Representation/Statemanager.cpp
        Representation/State.cpp
)

add_executable(pacman ${PACMAN_SOURCES})

target_link_libraries(pacman
        PRIVATE
        sfml-graphics
        sfml-window
        sfml-system
        GameLogic
)