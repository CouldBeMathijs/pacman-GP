cmake_minimum_required(VERSION 3.20)
project(pacman)

find_package(SFML 2.5 REQUIRED COMPONENTS graphics window system)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Werror)
#add_compile_options(-O0)

add_subdirectory(logic)

set(PACMAN_SOURCES
        main.cpp
        representation/Game.cpp
        representation/Statemanager.cpp
        representation/Camera.cpp
        representation/ConcreteEntityFactory.cpp
        representation/EntityView.cpp
        representation/state/MenuState.cpp
        representation/state/LevelState.cpp
        representation/state/PausedState.cpp
        representation/state/VictoryState.cpp
        representation/state/GameOverState.cpp
)

add_executable(pacman ${PACMAN_SOURCES})

target_link_libraries(pacman
        PRIVATE
        sfml-graphics
        sfml-window
        sfml-system
        GameLogic
)
