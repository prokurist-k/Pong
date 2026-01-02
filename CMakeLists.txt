cmake_minimum_required(VERSION 3.10)
project(Pong)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SDL2 REQUIRED)

include_directories(Source)
set(GAME_SOURCES
    Source/main.cpp
    Source/Components/Components.h
    Source/ECS/Entity.h
    Source/ECS/Entity.cpp
    Source/ECS/World.h
    Source/ECS/World.cpp
    Source/Game/Game.h
    Source/Game/Game.cpp
    Source/Math/Color.h
    Source/Math/Color.cpp
    Source/Math/Math.h
    Source/Math/Math.cpp
    Source/Math/Vector2.h
    Source/Math/Vector2.cpp
    Source/Systems/MovementSystem.h
    Source/Systems/MovementSystem.cpp
)
add_executable(Pong
    ${GAME_SOURCES}
)
target_link_libraries(Pong PRIVATE SDL2::SDL2)

if(TARGET SDL2::SDL2main)
    target_link_libraries(Pong PRIVATE SDL2::SDL2main)
endif()
