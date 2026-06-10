#include "GameStatePause.h"
#include "Game/Game.h"

void CGameStatePause::OnEnter(CGame* game)
{
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

std::string CGameStatePause::GetName() const
{
    return "Pause";
}
