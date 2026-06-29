#include "GameStatePause.h"
#include "Game/Game.h"

void CGameStatePause::OnEnter(CGame* game)
{
    game->PauseGame();
}

void CGameStatePause::OnExit()
{
}

void CGameStatePause::Update(CGame* game, float delta_seconds)
{
}

void CGameStatePause::Render(CGame* game)
{
}

void CGameStatePause::HandleInput(SDL_Event& event, CGame* game)
{
}

std::string CGameStatePause::GetName() const
{
    return "Pause";
}
