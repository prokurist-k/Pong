#ifndef GAMESTATE_PAUSE_H
#define GAMESTATE_PAUSE_H

#include "GameState.h"

class CGameStatePause : public IGameState
{
public:
    virtual void OnEnter(class CGame* game) override;
    virtual void OnExit(class CGame* game) override;

    virtual void Update(class CGame* game, float delta_seconds) override;
    virtual void Render(class CGame* game) override;

    virtual void HandleInput(SDL_Event& event, CGame* game) override;

    virtual std::string GetName() const override;
};

#endif // GAMESTATE_PAUSE_H
