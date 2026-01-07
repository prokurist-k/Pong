#ifndef GAME_H
#define GAME_H

#include "ECS/Entity.h"
#include "ECS/World.h"
#include "Systems/CollisionSystem.h"
#include "Systems/InputSystem.h"
#include "Systems/MovementSystem.h"
#include "Systems/RenderSystem.h"
#include <memory>
class CGame
{
public:
    bool Initialize(uint32 window_width, uint32 window_height);
    void Shutdown();

    void Run();

private:
    void ProcessInput();

    void Update(float delta_seconds);
    void Render();

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
};

#endif // GAME_H
