set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(LOGIC_SOURCES
        EntityModel.cpp
        EntityType/Collectable.cpp
        EntityType/Ghost.cpp
        EntityType/Pacman.cpp
        EntityType/Wall.cpp
        Position.cpp
        Random.cpp
        ScoreKeeper.cpp
        Stopwatch.cpp
        Subject.cpp
        Visitor.cpp
        World.cpp
)
add_compile_options(-Wall)

add_library(GameLogic STATIC ${LOGIC_SOURCES})

target_include_directories(GameLogic
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)