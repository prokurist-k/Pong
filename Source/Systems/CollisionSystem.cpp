#include "CollisionSystem.h"
#include "Audio/AudioManager.h"
#include "Components/Components.h"
#include "ECS/Entity.h"
#include "Math/AABB.h"
#include "Math/Math.h"
#include "Math/Vector2.h"

void CCollisionSystem::Update(CWorld& world)
{
    for (EntityId id = 0; id != MAX_ENTITIES; ++id)
    {
        if (!world.HasComponent(id, EComponentType::Tag) || !world.HasComponent(id, EComponentType::Transform) || !world.HasComponent(id, EComponentType::BoxCollider) || !world.HasComponent(id, EComponentType::Velocity))
        {
            continue;
        }

        CTagComponent& ball_tag_component = world.GetComponent<CTagComponent>(id);
        if (ball_tag_component.tag != ETag::Ball)
        {
            continue;
        }

        CTransformComponent& ball_transform_component = world.GetComponent<CTransformComponent>(id);
        CBoxColliderComponent& ball_box_collider_component = world.GetComponent<CBoxColliderComponent>(id);
        CVelocityComponent& ball_velocity_component = world.GetComponent<CVelocityComponent>(id);

        if (ball_transform_component.location.y < 0)
        {
            ball_transform_component.location.y = 0.0f;
            ball_velocity_component.direction.y *= -1.0f;
        }
        else if (ball_transform_component.location.y + ball_box_collider_component.size.y > world.GetWindowHeight())
        {
            ball_transform_component.location.y = world.GetWindowHeight() - ball_box_collider_component.size.y;
            ball_velocity_component.direction.y *= -1.0f;
        }
        // else if(ball_transform_component.location.x + ball_box_collider_component.size.x > world.GetWindowWidth())
        //{
        //     ball_transform_component.location.x = world.GetWindowWidth() - ball_box_collider_component.size.x;
        //     ball_velocity_component.direction.x *= -1.0f;
        // }

        for (EntityId other_id = 0; other_id != MAX_ENTITIES; other_id++)
        {
            if (id == other_id)
            {
                continue;
            }

            if (!world.HasComponent(other_id, EComponentType::Tag) || !world.HasComponent(other_id, EComponentType::Transform) || !world.HasComponent(other_id, EComponentType::BoxCollider))
            {
                continue;
            }

            CTransformComponent& other_transform_component = world.GetComponent<CTransformComponent>(other_id);
            CBoxColliderComponent& other_box_collider_component = world.GetComponent<CBoxColliderComponent>(other_id);
            CVelocityComponent& other_velocity_component = world.GetComponent<CVelocityComponent>(other_id);

            if (CheckAABB(ball_transform_component.location, ball_box_collider_component.size, other_transform_component.location, other_box_collider_component.size))
            {
                CTagComponent other_tag_component = world.GetComponent<CTagComponent>(other_id).tag;
                if (other_tag_component.tag == ETag::Wall)
                {
                    ball_velocity_component.direction.y *= -1.0f;
                }
                else if (other_tag_component.tag == ETag::Player)
                {
                    ball_transform_component.location.x = other_transform_component.location.x + other_box_collider_component.size.x + 0.1f;
                    ball_velocity_component.direction.x *= -1.0f;
                    CVector2 result = other_velocity_component.direction + ball_velocity_component.direction;
                    result.Normalize();
                    ball_velocity_component.direction = result;
                    CAudioManager::Get().PlaySound("ball_hit");
                    float angle = 0.0f;
                    for (uint8 i = 0; i != 30; ++i)
                    {
                        EntityId particle_id = world.CreateEntity();

                        world.AddComponent(particle_id, CTransformComponent(ball_transform_component.location, 0.0f, CVector2(3.0f, 3.0f)));

                        float spread = 1.5708f;
                        float random_offset = ((rand() % 2000) / 1000.0f - 1.0f) * spread;
                        float final_angle = angle + random_offset;

                        CVector2 direction(CMath::Cos(final_angle), CMath::Sin(final_angle));

                        float speed = static_cast<float>(rand() % 400 + 200);
                        world.AddComponent(particle_id, CVelocityComponent(direction, speed));
                        world.AddComponent(particle_id, CSpriteComponent(CColor(255, 200, 50, 255)));
                        world.AddComponent(particle_id, CParticleComponent(0.4f + (rand() % 30 / 100.0f)));
                    }
                }
                else if (other_tag_component.tag == ETag::Enemy)
                {
                    ball_transform_component.location.x = other_transform_component.location.x - ball_box_collider_component.size.x - 0.1f;
                    ball_velocity_component.direction.x *= -1.0f;
                    CVector2 result = other_velocity_component.direction + ball_velocity_component.direction;
                    result.Normalize();
                    ball_velocity_component.direction = result;
                    CAudioManager::Get().PlaySound("ball_hit");
                    float angle = CMath::PI;
                    for (uint8 i = 0; i != 30; ++i)
                    {
                        EntityId particle_id = world.CreateEntity();

                        world.AddComponent(particle_id, CTransformComponent(ball_transform_component.location, 0.0f, CVector2(3.0f, 3.0f)));

                        float spread = 1.5708f;
                        float random_offset = ((rand() % 2000) / 1000.0f - 1.0f) * spread;
                        float final_angle = angle + random_offset;

                        CVector2 direction(CMath::Cos(final_angle), CMath::Sin(final_angle));

                        float speed = static_cast<float>(rand() % 400 + 200);
                        world.AddComponent(particle_id, CVelocityComponent(direction, speed));
                        world.AddComponent(particle_id, CSpriteComponent(CColor(255, 200, 50, 255)));
                        world.AddComponent(particle_id, CParticleComponent(0.4f + (rand() % 30 / 100.0f)));
                    }
                }
            }
        }
    }
}
