set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(LOGIC_SOURCES
        IDirectionalEntityModel.cpp
        IEntityModel.cpp
        ISubject.cpp
        Position.cpp
        Random.cpp
        ScoreKeeper.cpp
        Stopwatch.cpp
        Visitor.cpp
        World.cpp
        WorldAsciiGridParser.cpp
        WorldCreator.cpp
        entityType/Collectable.cpp
        entityType/Ghost.cpp
        entityType/Pacman.cpp
        entityType/Wall.cpp
)
add_compile_options(-Wall -Wextra)

add_library(GameLogic STATIC ${LOGIC_SOURCES})

target_include_directories(GameLogic
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)