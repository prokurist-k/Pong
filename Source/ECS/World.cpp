#include "World.h"
#include "Components/Components.h"
#include "ECS/Entity.h"
#include "Math/Vector2.h"
#include <SDL_log.h>
#include <cstddef>

CWorld::CWorld()
    : currently_active_entites(0)
    , window_width(0)
    , window_height(0)
    , score_player1(0)
    , score_player2(0)
    , serve_timer(0.0f)
{
    for (EntityId i = 0; i != MAX_ENTITIES; ++i)
    {
        available_entity_ids.push(i);
    }

    signatures.resize(MAX_ENTITIES);

    transform_component_pool.resize(MAX_ENTITIES);
    velocity_component_pool.resize(MAX_ENTITIES);
    sprite_component_pool.resize(MAX_ENTITIES);
    input_component_pool.resize(MAX_ENTITIES);
    tag_component_pool.resize(MAX_ENTITIES);
    box_collider_component_pool.resize(MAX_ENTITIES);
    particle_component_pool.resize(MAX_ENTITIES);
}

bool CWorld::IsServing() const
{
    return serve_timer > 0.0f;
}

void CWorld::UpdateTimer(float dt)
{
    if (serve_timer > 0.0f)
    {
        serve_timer -= dt;
    }
}

EntityId CWorld::CreateEntity()
{
    if (currently_active_entites >= MAX_ENTITIES)
    {
        return INVALID_ENTITY_ID;
    }

    const EntityId new_entity_id = available_entity_ids.front();
    available_entity_ids.pop();
    currently_active_entites++;

    signatures[new_entity_id].reset();

    return new_entity_id;
}

void CWorld::DestroyEntity(const EntityId id)
{
    signatures[id].reset();
    available_entity_ids.push(id);
    currently_active_entites--;

    RemoveFromList(active_entities_for_rendering, id);
    RemoveFromList(active_entities_for_collision, id);
}

bool CWorld::HasComponent(EntityId id, EComponentType component_type)
{
    return signatures[id].test(component_type);
}

void CWorld::RemoveFromList(std::vector<EntityId>& list, const EntityId id)
{
    for (size_t i = 0; i < list.size(); ++i)
    {
        if (list[i] == id)
        {
            list[i] = list.back();
            list.pop_back();
            return;
        }
    }
}

void CWorld::UpdateCameraShake(float delta_seconds)
{
    if (camera_shake.duration > 0.0f)
    {
        camera_shake.duration -= delta_seconds;

        camera_shake.offset.x = (float)((rand() % 200) - 100) / 100.0f * camera_shake.intensity;
        camera_shake.offset.y = (float)((rand() % 200) - 100) / 100.0f * camera_shake.intensity;

        camera_shake.intensity *= 0.9f;
    }
    else
    {
        camera_shake.offset = CVector2::zero_vector;
    }
}

void CWorld::Clear()
{
    for (EntityId id = 0; id != MAX_ENTITIES; ++id)
    {
        if (signatures[id].any())
        {
            DestroyEntity(id);
        }
    }

    active_entities_for_collision.clear();
    active_entities_for_rendering.clear();

    score_player1 = 0;
    score_player2 = 0;
}
