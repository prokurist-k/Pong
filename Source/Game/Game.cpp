#include "Game.h"
#include "Components/Components.h"
#include "ECS/Entity.h"
#include "GameStates/GameState.h"
#include "GameStates/GameStateGame.h"
#include "GameStates/GameStateMainMenu.h"
#include "Math/Color.h"
#include "Math/Vector2.h"

#include <SDL_log.h>
#include <SDL_scancode.h>
#include <SDL_timer.h>
#include <memory>

#include <SDL2/SDL.h>
#include <SDL_events.h>
#include <SDL_render.h>

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"

bool CGame::Initialize()
{
    if (!InitializeSDL())
    {
        SDL_Log("Failed to initialize SDL");
        return false;
    }

    if (!InitializeImgui())
    {
        SDL_Log("Failed to initialize imgui");
        return false;
    }

    if (!InitializeECS())
    {
        SDL_Log("Failed to initialize ESC");
        return false;
    }

    CreateEntities();

    // ChangeGameState(new CGameStateGame());
    ChangeGameState(new CGameStateMainMenu());

    return is_running = true;
}

void CGame::Shutdown()
{
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_Quit();
}

void CGame::Run()
{
    while (is_running)
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

void CGame::ChangeGameState(IGameState* new_state)
{
    if (current_state)
    {
        current_state->OnExit();
    }

    current_state.reset(new_state);
    current_state->OnEnter(this);
}

void CGame::StartGame()
{
    ChangeGameState(new CGameStateGame);
}

void CGame::ExitGame()
{
    is_running = false;
}

void CGame::PauseGame()
{
}

bool CGame::InitializeSDL()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow(
        game_config.window_title.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        game_config.window_width, game_config.window_height,
        SDL_WINDOW_SHOWN);

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
    return true;
}

bool CGame::InitializeImgui()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    io.FontGlobalScale = 2.0f;

    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer2_Init(renderer);

    ImGui::StyleColorsDark();
    return true;
}

bool CGame::InitializeECS()
{
    world = std::make_unique<CWorld>();
    if (!world)
    {
        SDL_Log("Failed to create world");
        return false;
    }
    world->SetWindowSize(game_config.window_width, game_config.window_height);

    render_system = std::make_unique<CRenderSystem>(renderer);
    if (!render_system)
    {
        SDL_Log("Failed to create render system");
        return false;
    }
    movement_system = std::make_unique<CMovementSystem>();
    if (!movement_system)
    {
        SDL_Log("Failed to create movement system");
        return false;
    }
    input_system = std::make_unique<CInputSystem>();
    if (!input_system)
    {
        SDL_Log("Failed to create input system");
        return false;
    }
    collision_system = std::make_unique<CCollisionSystem>();
    if (!collision_system)
    {
        SDL_Log("Failed to create collision system");
        return false;
    }
    game_rules_system = std::make_unique<CGameRulesSystem>();
    if (!game_rules_system)
    {
        SDL_Log("Failed to create game rules system");
        return false;
    }
    return true;
}

void CGame::CreateEntities()
{
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

    float player_location_x = game_config.paddle_offset_x;
    float player_location_y = (game_config.window_height / 2.0f) - (game_config.paddle_height / 2.0f);
    player_paddle = CreatePaddle(CVector2(player_location_x, player_location_y), SDL_SCANCODE_W, SDL_SCANCODE_S, ETag::Player);

    float enemy_location_x = game_config.window_width - game_config.paddle_offset_x - game_config.paddle_width;
    float enemy_location_y = (game_config.window_height / 2.0f) - (game_config.paddle_height / 2.0f);
    enemy_paddle = CreatePaddle(CVector2(enemy_location_x, enemy_location_y), SDL_SCANCODE_UP, SDL_SCANCODE_DOWN, ETag::Enemy);
}

EntityId CGame::CreatePaddle(const CVector2& position, SDL_Scancode up, SDL_Scancode down, ETag tag)
{
    EntityId paddle = world->CreateEntity();

    world->AddComponent<CTransformComponent>(paddle, CTransformComponent(position, 0.0f, CVector2(game_config.paddle_width, game_config.paddle_height)));
    world->AddComponent<CSpriteComponent>(paddle, CSpriteComponent(CColor::white));

    world->AddComponent<CInputComponent>(paddle, CInputComponent(up, down, game_config.paddle_speed));
    world->AddComponent<CVelocityComponent>(paddle, CVelocityComponent());

    world->AddComponent<CBoxColliderComponent>(paddle, CBoxColliderComponent(CVector2(game_config.paddle_width, game_config.paddle_height)));
    world->AddComponent<CTagComponent>(paddle, CTagComponent(tag));

    return paddle;
}

void CGame::ProcessInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        ImGui_ImplSDL2_ProcessEvent(&event);
        if (event.type == SDL_QUIT)
        {
            is_running = false;
        }
    }
}

void CGame::Update(float delta_seconds)
{
    world->UpdateTimer(delta_seconds);

    if (current_state)
    {
        current_state->Update(this, delta_seconds);
    }
}

void CGame::Render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    if (current_state)
    {
        current_state->Render(this);
    }

    SDL_RenderPresent(renderer);
}
