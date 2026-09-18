cmake_minimum_required(VERSION 3.20)

project(SFMLTest LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)

add_executable(MainTest
    src/main.cpp
    src/map.cpp
    src/robot.cpp
    src/cell.cpp
    src/player.cpp
    src/enemy.cpp
    src/game.cpp
)

target_link_libraries(MainTest PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
)