#ifndef WORLD_H
#define WORLD_H

#include "Entity.h"
#include "Components/Components.h"

#include <vector>
#include <queue>

class CWorld
{
    public:
        CWorld();

        EntityId CreateEntity();
        void DestroyEntity(const EntityId id);

        bool HasComponent(EntityId id, EComponentType component_type);

        template<typename T>
        void AddComponent(EntityId id, T& component)
        {
            if constexpr(std::is_same_v<T, CTransformComponent>)
            {
                transform_component_pool[id] = component;
                signatures[id].set(EComponentType::Transform, true);
            }
            else if constexpr(std::is_same_v<T, CVelocityComponent>)
            {
                velocity_component_pool[id] = component;
                signatures[id].set(EComponentType::Velocity, true);
            }
            else if constexpr(std::is_same_v<T, CSpriteComponent>)
            {
                sprite_component_pool[id] = component;
                signatures[id].set(EComponentType::Sprite, true);
            }
            else if constexpr(std::is_same_v<T, CInputComponent>)
            {
                input_component_pool[id] = component;
                signatures[id].set(EComponentType::Input, true);
            }
        }

        template<typename T>
        void AddComponent(EntityId id, T&& component)
        {
            if constexpr(std::is_same_v<T, CTransformComponent>)
            {
                transform_component_pool[id] = component;
                signatures[id].set(EComponentType::Transform, true);
            }
            else if constexpr(std::is_same_v<T, CVelocityComponent>)
            {
                velocity_component_pool[id] = component;
                signatures[id].set(EComponentType::Velocity, true);
            }
            else if constexpr(std::is_same_v<T, CSpriteComponent>)
            {
                sprite_component_pool[id] = component;
                signatures[id].set(EComponentType::Sprite, true);
            }
            else if constexpr(std::is_same_v<T, CInputComponent>)
            {
                input_component_pool[id] = component;
                signatures[id].set(EComponentType::Input, true);
            }
        }

        template<typename T>
        T& GetComponent(const EntityId id)
        {
            if constexpr(std::is_same_v<T, CTransformComponent>)
            {
                return transform_component_pool[id];
            }
            else if constexpr (std::is_same_v<T, CVelocityComponent>)
            {
                return velocity_component_pool[id];
            }
            else if constexpr (std::is_same_v<T, CSpriteComponent>)
            {
                return sprite_component_pool[id];
            }
            else if constexpr (std::is_same_v<T, CInputComponent>)
            {
                return input_component_pool[id];
            }
        }

    private:
        uint32 currently_active_entites;
        std::queue<EntityId> available_entity_ids;
        std::vector<Signature> signatures;

        std::vector<CTransformComponent> transform_component_pool;
        std::vector<CVelocityComponent> velocity_component_pool;
        std::vector<CSpriteComponent> sprite_component_pool;
        std::vector<CInputComponent> input_component_pool;
};

#endif // WORLD_H
