#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H

#include "ECS/World.h"

class CParticleSystem
{
public:
    void Update(CWorld& world, const float delta_seconds);
};

#endif
