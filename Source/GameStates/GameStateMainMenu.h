#ifndef GAMESTATE_MAIN_MENU_H
#define GAMESTATE_MAIN_MENU_H

#include "GameState.h"

class CGameStateMainMenu : public IGameState
{
public:
    virtual void OnEnter(class CGame* game) override;
    virtual void OnExit() override;

    virtual void Update(class CGame* game, float delta_seconds) override;
    virtual void Render(class CGame* game) override;

    virtual std::string GetName() const override;
};

#endif // GAMESTATE_MAIN_MENU_H
