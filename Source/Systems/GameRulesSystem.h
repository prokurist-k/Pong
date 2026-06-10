#ifndef GAME_RULES_SYSTEM_H
#define GAME_RULES_SYSTEM_H

#include "ECS/World.h"

class CGameRulesSystem
{
public:
    CGameRulesSystem() = default;
    void Update(CWorld& world);

private:
    void ResetBall(CWorld& world, CTransformComponent& transform_component, CVelocityComponent& velocity_component, float direction_x);
};

#endif
