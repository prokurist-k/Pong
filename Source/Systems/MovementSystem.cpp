#include "MovementSystem.h"
#include "Components/Components.h"
#include "ECS/Entity.h"

CMovementSystem::CMovementSystem()
{

}

void CMovementSystem::Update(CWorld& world, const float delta_seconds)
{
    for(EntityId id = 0; id != MAX_ENTITES; ++id)
    {
        if(!world.HasComponent(id, EComponentType::Transform) ||
            !world.HasComponent(id, EComponentType::Velocity))
        {
            continue;
        }

        CTransformComponent& transform_component = world.GetComponent<CTransformComponent>(id);
        CVelocityComponent& velocity_component = world.GetComponent<CVelocityComponent>(id);

        transform_component.location += velocity_component.direction * (velocity_component.speed * delta_seconds);
    }
}
