#include "Game.h"
#include "Components/Components.h"
#include "Math/Color.h"
#include "Math/Vector2.h"

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
            game_config.window_width, game_config.window_height,
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
    world->SetWindowSize(game_config.window_width, game_config.window_height);
    render_system = std::make_unique<CRenderSystem>(renderer);
    movement_system = std::make_unique<CMovementSystem>();
    input_system = std::make_unique<CInputSystem>();
    collision_system = std::make_unique<CCollisionSystem>();

    ball = world->CreateEntity();
    world->AddComponent<CBoxColliderComponent>(ball, CBoxColliderComponent(CVector2(game_config.ball_size)));

    CVector2 window_size(game_config.window_width, game_config.window_height);

    CVector2 ball_size(game_config.ball_size, game_config.ball_size);
    CVector2 ball_start_position = (window_size / 2.0f) - (ball_size / 2.0f);

    world->AddComponent<CTransformComponent>(ball, CTransformComponent(CVector2(ball_start_position.x, ball_start_position.y), 0.0f, CVector2(game_config.ball_size)));
    world->AddComponent<CSpriteComponent>(ball, CSpriteComponent(CColor::white));

    CVector2 ball_direction(-1.0f, 0.0f);
    ball_direction.Normalize();
    const float ball_speed = game_config.ball_start_speed;
    world->AddComponent<CVelocityComponent>(ball, CVelocityComponent(ball_direction, ball_speed));
    world->AddComponent<CTagComponent>(ball, CTagComponent(ETag::Ball));

    CVector2 player_paddle_start_position = CVector2(game_config.paddle_offset_x, (game_config.window_height / 2.0f) - (game_config.paddle_height / 2.0f));

    player_paddle = world->CreateEntity();
    world->AddComponent<CTransformComponent>(player_paddle, CTransformComponent(player_paddle_start_position, 0.0f, CVector2(game_config.paddle_width, game_config.paddle_height)));
    world->AddComponent<CSpriteComponent>(player_paddle, CSpriteComponent(CColor::white));
    world->AddComponent<CInputComponent>(player_paddle, CInputComponent(SDL_SCANCODE_W, SDL_SCANCODE_S, game_config.paddle_speed));
    world->AddComponent<CVelocityComponent>(player_paddle, CVelocityComponent());
    world->AddComponent<CTagComponent>(player_paddle, CTagComponent(ETag::Player));
    world->AddComponent<CBoxColliderComponent>(player_paddle, CBoxColliderComponent(CVector2(game_config.paddle_width, game_config.paddle_height)));

    CVector2 enemy_paddle_start_position = CVector2(game_config.window_width - game_config.paddle_offset_x - game_config.paddle_width, (game_config.window_height / 2.0f) - (game_config.paddle_height / 2.0f));

    enemy_paddle = world->CreateEntity();
    world->AddComponent<CTransformComponent>(enemy_paddle, CTransformComponent(enemy_paddle_start_position, 0.0f, CVector2(game_config.paddle_width, game_config.paddle_height)));
    world->AddComponent<CSpriteComponent>(enemy_paddle, CSpriteComponent(CColor::white));
    world->AddComponent<CInputComponent>(enemy_paddle, CInputComponent(SDL_SCANCODE_UP, SDL_SCANCODE_DOWN, game_config.paddle_speed));
    world->AddComponent<CVelocityComponent>(enemy_paddle, CVelocityComponent());
    world->AddComponent<CTagComponent>(enemy_paddle, CTagComponent(ETag::Enemy));
    world->AddComponent<CBoxColliderComponent>(enemy_paddle, CBoxColliderComponent(CVector2(game_config.paddle_width, game_config.paddle_height)));

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
        {
            delta_seconds = 0.05f;
        }

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
    collision_system->Update(*world);
}

void CGame::Render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    render_system->Update(*world);

    SDL_RenderPresent(renderer);
}
