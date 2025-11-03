set(LOGIC_SOURCES
        Random.cpp
        Stopwatch.cpp
        Subject.cpp
        entity_types/Collectable.cpp
        entity_types/Ghost.cpp
        entity_types/Pacman.cpp
        entity_types/Wall.cpp
        World.cpp
        AbstractEntityFactory.cpp
        AbstractEntityFactory.h
        Observer.cpp
        Observer.h
        Score.cpp
        Score.h
)
add_compile_options(-Wall)

add_library(GameLogic STATIC ${LOGIC_SOURCES})

target_include_directories(GameLogic
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)