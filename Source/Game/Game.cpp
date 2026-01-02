#include "Game.h"
#include "Components/Components.h"
#include "Math/Color.h"
#include "Math/Vector2.h"
#include "Systems/RenderSystem.h"
#include <SDL2/SDL.h>
#include <SDL_events.h>
#include <SDL_render.h>
#include <memory>

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

    ball = world->CreateEntity();

    world->AddComponent<CTransformComponent>(ball, CTransformComponent(CVector2::zero_vector));
    world->AddComponent<CSpriteComponent>(ball, CSpriteComponent(CLinearColor::white));

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

}

void CGame::Render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);



    SDL_RenderPresent(renderer);
}
