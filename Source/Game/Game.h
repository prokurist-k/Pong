#ifndef GAME_H
#define GAME_H

#include "ECS/Entity.h"
#include "ECS/World.h"
#include "Systems/RenderSystem.h"
#include <memory>
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

    class SDL_Window* window = nullptr;
    class SDL_Renderer* renderer = nullptr;
    bool is_running = false;

    std::unique_ptr<CWorld> world;
    std::unique_ptr<CRenderSystem> render_system;

    EntityId ball;
};

#endif // GAME_H
