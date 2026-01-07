#ifndef COLLISION_SYSTEM_H
#define COLLISION_SYSTEM_H

#include "ECS/World.h"

class CCollisionSystem
{
public:
    CCollisionSystem() = default;

    void Update(CWorld& world);
};

#endif // COLLISION_SYSTEM_H
