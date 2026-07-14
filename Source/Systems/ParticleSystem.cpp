#include "ParticleSystem.h"
#include "Components/Components.h"
#include <SDL_assert.h>
#include <SDL_log.h>

void CParticleSystem::Update(CWorld& world, const float delta_seconds)
{
    for (EntityId id = 0; id != MAX_ENTITIES; ++id)
    {
        if (!world.HasComponent(id, EComponentType::Particle))
            continue;

        auto& particle = world.GetComponent<CParticleComponent>(id);
        particle.lifetime -= delta_seconds;

        if (particle.lifetime <= 0.f)
        {
            world.DestroyEntity(id);
        }
    }
}
