#ifndef GAMESTATE_GAME_H
#define GAMESTATE_GAME_H

#include "GameState.h"

class CGameStateGame : public IGameState
{
public:
    virtual void OnEnter(class CGame* game) override;
    virtual void OnExit() override;

    virtual void Update(class CGame* game, float delta_seconds) override;
    virtual void Render(class CGame* game) override;

    virtual std::string GetName() const override;
};

#endif // GAMESTATE_GAME_H
