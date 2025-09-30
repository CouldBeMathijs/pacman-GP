cmake_minimum_required(VERSION 3.20)
project(pacman)


find_package(SFML 2.5 REQUIRED COMPONENTS graphics window system)
set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES
)
add_executable(pacman ${SOURCE_FILES})
target_link_libraries(pacman sfml-graphics sfml-window sfml-system)
