#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SDL_events.h>
#include <string>
class IGameState
{
public:
    virtual ~IGameState() = default;

    virtual void OnEnter(class CGame* game) = 0;
    virtual void OnExit() = 0;

    virtual void Update(class CGame* game, float delta_seconds) = 0;
    virtual void Render(class CGame* game) = 0;

    virtual void HandleInput(SDL_Event& event, CGame* game) = 0;

    virtual std::string GetName() const = 0;
};

#endif // GAMESTATE_H
