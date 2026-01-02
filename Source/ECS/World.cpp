#include "World.h"
#include "Components/Components.h"
#include "ECS/Entity.h"

CWorld::CWorld()
    : currently_active_entites(0)
{
    for(EntityId i = 0; i != MAX_ENTITES; ++i)
    {
        available_entity_ids.push(i);
    }

    signatures.resize(MAX_ENTITES);

    transform_component_pool.resize(MAX_ENTITES);
    velocity_component_pool.resize(MAX_ENTITES);
    sprite_component_pool.resize(MAX_ENTITES);
}

EntityId CWorld::CreateEntity()
{
    if(currently_active_entites >= MAX_ENTITES)
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
