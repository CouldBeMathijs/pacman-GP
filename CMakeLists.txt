cmake_minimum_required(VERSION 3.28.3)
project(pacman)

find_package(SFML 2.5 REQUIRED COMPONENTS graphics window system)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall)
#add_compile_options(-O0)

add_subdirectory(logic)

set(PACMAN_SOURCES
        main.cpp
        representation/AssetManager.cpp
        representation/Camera.cpp
        representation/ViewCompatibleEntityFactory.cpp
        representation/EntityView.cpp
        representation/Game.cpp
        representation/ScoreView.cpp
        representation/StateManager.cpp
        representation/state/GameOverState.cpp
        representation/state/LevelState.cpp
        representation/state/MenuState.cpp
        representation/state/PausedState.cpp
        representation/state/VictoryState.cpp
)

add_executable(pacman ${PACMAN_SOURCES})

target_link_libraries(pacman
        PRIVATE
        sfml-graphics
        sfml-window
        sfml-system
        GameLogic
)
