cmake_minimum_required(VERSION 3.20)

project(SFMLTest LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)

add_executable(MainTest
    src/application.cpp
    src/main.cpp
    src/map.cpp
    src/robot.cpp
    src/cell.cpp
    src/player.cpp
    src/game.cpp
    src/visualization.cpp
    src/controls.cpp
    src/position.h
    src/position.cpp
    src/factory.cpp
    src/abilities/AbilityInfo.cpp
    src/abilities/AroundHit.cpp
    src/abilities/AbilityInfo.h
    src/abilities/FarHit.cpp
    src/abilities/Heal.cpp
    src/abilities/Teleport.cpp
    src/statuses/Burn.cpp
    src/statuses/Slowth.cpp
    src/statuses/Overload.cpp
    src/statuses/Shield.cpp
)

target_link_libraries(MainTest PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
)
