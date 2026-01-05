#include "Game.h"
#include "Components/Components.h"
#include "Math/Color.h"
#include "Math/Vector2.h"
#include "Systems/InputSystem.h"
#include "Systems/MovementSystem.h"

#include <SDL_scancode.h>
#include <SDL_timer.h>
#include <memory>

#include <SDL2/SDL.h>
#include <SDL_events.h>
#include <SDL_render.h>

bool CGame::Initialize()
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow
        (
            "Pong",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            800, 600,
            SDL_WINDOW_SHOWN
        );

    if (window == nullptr)
    {
        SDL_Log("SDL_CreateWindow failed: %s", SDL_GetError());
        SDL_Quit();
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr)
    {
        SDL_Log("SDL_CreateRenderer failed: %s", SDL_GetError());
        SDL_Quit();
        return false;
    }

    world = std::make_unique<CWorld>();
    render_system = std::make_unique<CRenderSystem>(renderer);
    movement_system = std::make_unique<CMovementSystem>();
    input_system = std::make_unique<CInputSystem>();

    ball = world->CreateEntity();
    world->AddComponent<CTransformComponent>(ball, CTransformComponent(CVector2(10.0f, 10.0f), 0.0f, CVector2(10.0f, 10.0f)));
    world->AddComponent<CSpriteComponent>(ball, CSpriteComponent(CColor::white));

    CVector2 ball_direction(1.0f, 0.5f);
    ball_direction.Normalize();
    const float ball_speed = 300;
    world->AddComponent<CVelocityComponent>(ball, CVelocityComponent(ball_direction, ball_speed));

    player_paddle = world->CreateEntity();
    world->AddComponent<CTransformComponent>(player_paddle, CTransformComponent(CVector2(10.0f, 10.0f), 0.0f, CVector2(10.0f, 60.0f)));
    world->AddComponent<CSpriteComponent>(player_paddle, CSpriteComponent(CColor::white));
    world->AddComponent<CInputComponent>(player_paddle, CInputComponent(SDL_SCANCODE_W, SDL_SCANCODE_S, 400.0f));
    world->AddComponent<CVelocityComponent>(player_paddle, CVelocityComponent());

    return is_running = true;
}

void CGame::Shutdown()
{

}

void CGame::Run()
{
    while(is_running)
    {
        ProcessInput();

        uint64 current_tick_time = SDL_GetTicks64();
        float delta_seconds = (current_tick_time - last_tick_time) / 1000.0f;
        last_tick_time = current_tick_time;

        if (delta_seconds > 0.05f)
            delta_seconds = 0.05f;

        Update(delta_seconds);
        Render();
    }
}

void CGame::ProcessInput()
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT)
        {
            is_running = false;
        }
    }
}

void CGame::Update(float delta_seconds)
{
    input_system->Update(*world);
    movement_system->Update(*world, delta_seconds);
}

void CGame::Render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    render_system->Update(*world);

    SDL_RenderPresent(renderer);
}
