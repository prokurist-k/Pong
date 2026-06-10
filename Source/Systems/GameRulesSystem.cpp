#include "GameRulesSystem.h"
#include "ECS/Entity.h"

void CGameRulesSystem::Update(CWorld& world)
{
    for (EntityId id = 0; id != MAX_ENTITIES; ++id)
    {
        if (!world.HasComponent(id, EComponentType::Tag) || !world.HasComponent(id, EComponentType::Transform) || !world.HasComponent(id, EComponentType::Velocity))
        {
            continue;
        }

        if (world.GetComponent<CTagComponent>(id).tag != ETag::Ball)
        {
            continue;
        }

        CTransformComponent& transform = world.GetComponent<CTransformComponent>(id);
        CVelocityComponent& velocity = world.GetComponent<CVelocityComponent>(id);

        if (transform.location.x < 0.0f)
        {
            world.AddScoreP2();
            ResetBall(world, transform, velocity, -1.0f);
        }
        else if (transform.location.x > world.GetWindowWidth())
        {
            world.AddScoreP1();
            ResetBall(world, transform, velocity, 1.0f);
        }
    }
}

void CGameRulesSystem::ResetBall(CWorld& world, CTransformComponent& transform_component, CVelocityComponent& velocity_component, float direction_x)
{
    float center_x = world.GetWindowWidth() / 2.0f;
    float center_y = world.GetWindowHeight() / 2.0f;

    transform_component.location.x = center_x - (transform_component.scale.x / 2.0f);
    transform_component.location.y = center_y - (transform_component.scale.y / 2.0f);

    velocity_component.speed = 300.0f;

    velocity_component.direction = CVector2(direction_x, 0.0f);
    velocity_component.direction.Normalize();

    world.StartServeTimer(3.0f);
}
