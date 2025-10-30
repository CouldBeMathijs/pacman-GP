set(LOGIC_SOURCES
        Stopwatch.cpp
        World.cpp
        Random.cpp
        Random.h
)

add_library(GameLogic STATIC ${LOGIC_SOURCES})

target_include_directories(GameLogic
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)