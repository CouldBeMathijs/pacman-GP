set(LOGIC_SOURCES
        Random.cpp
        Stopwatch.cpp
        Subject.cpp
        Types/Collectable.cpp
        Types/Ghost.cpp
        Types/Pacman.cpp
        Types/Wall.cpp
        World.cpp
)
add_compile_options(-Wall)

add_library(GameLogic STATIC ${LOGIC_SOURCES})

target_include_directories(GameLogic
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)