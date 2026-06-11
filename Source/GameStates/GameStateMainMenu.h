#ifndef GAMESTATE_MAIN_MENU_H
#define GAMESTATE_MAIN_MENU_H

#include "CoreTypes.h"
#include "GameState.h"

class CGameStateMainMenu : public IGameState
{
public:
    virtual void OnEnter(class CGame* game) override;
    virtual void OnExit() override;

    virtual void Update(class CGame* game, float delta_seconds) override;
    virtual void Render(class CGame* game) override;

    virtual void HandleInput(SDL_Event& event, CGame* game) override;

    virtual std::string GetName() const override;

private:
    const float button_width = 200.f;
    const uint8 max_buttons = 2;

    const char* labels[2] = { "Start Game", "Exit" };

    int8 selected_button_index = 0;
};

#endif // GAMESTATE_MAIN_MENU_H
