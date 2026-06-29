cmake_minimum_required(VERSION 3.10)
project(Pong)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SDL2 REQUIRED)

set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/imgui)
set(MINIAUDIO_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/miniaudio)

set(GAME_SOURCES
    Source/main.cpp
    Source/Audio/AudioImplementation.cpp
    Source/Audio/AudioManager.h
    Source/Audio/AudioManager.cpp
    Source/Components/Components.h
    Source/Debug/DebugInspector.h
    Source/Debug/DebugInspector.cpp
    Source/ECS/Entity.h
    Source/ECS/Entity.cpp
    Source/ECS/World.h
    Source/ECS/World.cpp
    Source/Game/Game.h
    Source/Game/Game.cpp
    Source/GameStates/GameState.h
    Source/GameStates/GameStateGame.h
    Source/GameStates/GameStateGame.cpp
    Source/GameStates/GameStateMainMenu.h
    Source/GameStates/GameStateMainMenu.cpp
    Source/GameStates/GameStatePause.h
    Source/GameStates/GameStatePause.cpp
    Source/Math/AABB.h
    Source/Math/Color.h
    Source/Math/Color.cpp
    Source/Math/Math.h
    Source/Math/Math.cpp
    Source/Math/Vector2.h
    Source/Math/Vector2.cpp
    Source/Misc/Paths.h
    Source/Misc/Paths.cpp
    Source/Systems/CollisionSystem.h
    Source/Systems/CollisionSystem.cpp
    Source/Systems/GameRulesSystem.h
    Source/Systems/GameRulesSystem.cpp
    Source/Systems/InputSystem.h
    Source/Systems/InputSystem.cpp
    Source/Systems/MovementSystem.h
    Source/Systems/MovementSystem.cpp
    Source/Systems/RenderSystem.h
    Source/Systems/RenderSystem.cpp
)

set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/backends/imgui_impl_sdl2.cpp
    ${IMGUI_DIR}/backends/imgui_impl_sdlrenderer2.cpp
)

add_executable(Pong
    ${GAME_SOURCES}
    ${IMGUI_SOURCES}
)

target_include_directories(Pong PRIVATE
    Source
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
    ${MINIAUDIO_DIR}
)

target_link_libraries(Pong PRIVATE
    SDL2::SDL2
)

if(TARGET SDL2::SDL2main)
    target_link_libraries(Pong PRIVATE SDL2::SDL2main)
endif()
