#include "GameStateGame.h"
#include "Game/Game.h"
#include <SDL_keycode.h>

void CGameStateGame::OnEnter(CGame* game)
{
}

void CGameStateGame::OnExit()
{
}

void CGameStateGame::Update(CGame* game, float delta_seconds)
{
    game->GetWorld().UpdateTimer(delta_seconds);

    if (!game->GetWorld().IsServing())
    {
        game->GetInputSystem().Update(game->GetWorld());
        game->GetMovementSystem().Update(game->GetWorld(), delta_seconds);
        game->GetCollisionSystem().Update(game->GetWorld());
        game->GetGameRulesSystem().Update(game->GetWorld());
    }
}

void CGameStateGame::Render(CGame* game)
{
    game->GetRenderSystem().Update(game->GetWorld());
}

void CGameStateGame::HandleInput(SDL_Event& event, CGame* game)
{
}

std::string CGameStateGame::GetName() const
{
    return "Game";
}
