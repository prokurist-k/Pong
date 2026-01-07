#ifndef GAME_H
#define GAME_H

#include "ECS/Entity.h"
#include "ECS/World.h"
#include "Systems/CollisionSystem.h"
#include "Systems/InputSystem.h"
#include "Systems/MovementSystem.h"
#include "Systems/RenderSystem.h"

#include <memory>

struct SGameConfig
{
    uint32 window_width = 800;
    uint32 window_height = 600;
    std::string window_title = "Pong";

    float ball_size = 15.0f;
    float ball_start_speed = 300.0f;

    float paddle_width = 20.0f;
    float paddle_height = 100.0f;
    float paddle_speed = 400.0f;
    float paddle_offset_x = 30.0f;

    uint32 winning_score = 10;
};

class CGame
{
public:
    bool Initialize();
    void Shutdown();

    void Run();

private:
    void ProcessInput();

    void Update(float delta_seconds);
    void Render();

private:
    SGameConfig game_config;

    class SDL_Window* window = nullptr;
    class SDL_Renderer* renderer = nullptr;
    bool is_running = false;

    std::unique_ptr<CWorld> world;
    std::unique_ptr<CRenderSystem> render_system;
    std::unique_ptr<CMovementSystem> movement_system;
    std::unique_ptr<CInputSystem> input_system;
    std::unique_ptr<CCollisionSystem> collision_system;

    uint64 last_tick_time = 0;

    EntityId ball;
    EntityId player_paddle;
    EntityId enemy_paddle;
};

#endif // GAME_H
