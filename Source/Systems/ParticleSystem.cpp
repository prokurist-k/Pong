#include "ParticleSystem.h"
#include "Components/Components.h"

void CParticleSystem::Update(CWorld& world, const float delta_seconds)
{
    for (EntityId id = 0; id != MAX_ENTITIES; ++id)
    {
        if (!world.HasComponent(id, EComponentType::Particle))
            continue;

        auto& particle = world.GetComponent<CParticleComponent>(id);
        auto& velocity = world.GetComponent<CVelocityComponent>(id);
        auto& sprite = world.GetComponent<CSpriteComponent>(id);

        particle.lifetime -= delta_seconds;

        if (particle.lifetime <= 0.f)
        {
            world.DestroyEntity(id);
        }
        else
        {
            // sprite.color.a = static_cast<uint8>((particle.lifetime / particle.initial_lifetime) * 255);
            // // velocity.direction.x += (rand() % 11 - 5) * 0.1f;

            // // friction
            // // velocity.speed *= 0.95f;

            // // gravity
            // velocity.direction.y += 0.5f * delta_seconds;
            // velocity.direction.Normalize();

            // // shaking
            // velocity.direction.x += (rand() % 11 - 5) * 0.01f;
        }
    }
}
