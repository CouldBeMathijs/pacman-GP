cmake_minimum_required(VERSION 3.20)
project(pacman)


find_package(SFML 2.5 REQUIRED COMPONENTS graphics window system)
set(CMAKE_CXX_STANDARD 23)
set(SOURCE_FILES
        main.cpp
        Representation/Game.cpp
        Representation/Game.h
        Representation/Statemanager.cpp
        Representation/Statemanager.h
        Representation/State.cpp
        Representation/State.h
)
add_executable(pacman ${SOURCE_FILES})
target_link_libraries(pacman sfml-graphics sfml-window sfml-system)
