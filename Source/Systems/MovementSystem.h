#ifndef MOVEMENT_SYSTEM_H
#define MOVEMENT_SYSTEM_H

#include "ECS/World.h"

class CMovementSystem
{
public:
    CMovementSystem();

    void Update(CWorld& world, const float delta_seconds);
};

#endif // MOVEMENT_SYSTEM_H
