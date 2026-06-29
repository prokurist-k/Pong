#ifndef GAMESTATE_GAME_H
#define GAMESTATE_GAME_H

#include "CoreTypes.h"
#include "GameState.h"

class CGameStateGame : public IGameState
{
public:
    virtual void OnEnter(class CGame* game) override;
    virtual void OnExit() override;

    virtual void Update(class CGame* game, float delta_seconds) override;
    virtual void Render(class CGame* game) override;

    virtual void HandleInput(SDL_Event& event, CGame* game) override;

    virtual std::string GetName() const override;

private:
    const char* labels[2] = { "Resume", "Exit" };
    int8 selected_button_index = 0;
    const float button_width = 200.f;
    uint8 max_buttons = 0;
};

#endif // GAMESTATE_GAME_H
