#include "World.h"
#include "Components/Components.h"
#include "ECS/Entity.h"

CWorld::CWorld()
    : currently_active_entites(0)
    , window_width(0)
    , window_height(0)
{
    for(EntityId i = 0; i != MAX_ENTITIES; ++i)
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
}

void CWorld::SetWindowSize(const uint32 in_width, const uint32 in_height)
{
    window_width = in_width;
    window_height = in_height;
}

uint32 CWorld::GetWindowWidth() const
{
    return window_width;
}

uint32 CWorld::GetWindowHeight() const
{
    return window_height;
}

EntityId CWorld::CreateEntity()
{
    if(currently_active_entites >= MAX_ENTITIES)
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
}

bool CWorld::HasComponent(EntityId id, EComponentType component_type)
{
    return signatures[id].test(component_type);
}
