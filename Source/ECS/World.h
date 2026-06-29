#ifndef WORLD_H
#define WORLD_H

#include "Components/Components.h"
#include "Entity.h"

#include <queue>
#include <type_traits>
#include <utility>
#include <vector>

class CWorld
{
public:
    CWorld();

    void SetWindowSize(const uint32 in_width, const uint32 in_height);
    uint32 GetWindowWidth() const;
    uint32 GetWindowHeight() const;

    void AddScoreP1();
    void AddScoreP2();
    uint32 GetScoreP1() const
    {
        return score_player1;
    }
    uint32 GetScoreP2() const
    {
        return score_player2;
    }

    void StartServeTimer(float duration);
    bool IsServing() const;
    void UpdateTimer(float dt);

    EntityId CreateEntity();
    void DestroyEntity(const EntityId id);

    bool HasComponent(EntityId id, EComponentType component_type);

    template <typename T>
    void AddComponent(EntityId id, T&& component)
    {
        using ComponentType = std::decay_t<T>;

        if constexpr (std::is_same_v<ComponentType, CTransformComponent>)
        {
            transform_component_pool[id] = std::forward<T>(component);
            signatures[id].set(EComponentType::Transform, true);
        }
        else if constexpr (std::is_same_v<ComponentType, CVelocityComponent>)
        {
            velocity_component_pool[id] = std::forward<T>(component);
            signatures[id].set(EComponentType::Velocity, true);
        }
        else if constexpr (std::is_same_v<ComponentType, CSpriteComponent>)
        {
            sprite_component_pool[id] = std::forward<T>(component);
            signatures[id].set(EComponentType::Sprite, true);
        }
        else if constexpr (std::is_same_v<ComponentType, CInputComponent>)
        {
            input_component_pool[id] = std::forward<T>(component);
            signatures[id].set(EComponentType::Input, true);
        }
        else if constexpr (std::is_same_v<ComponentType, CTagComponent>)
        {
            tag_component_pool[id] = std::forward<T>(component);
            signatures[id].set(EComponentType::Tag, true);
        }
        else if constexpr (std::is_same_v<ComponentType, CBoxColliderComponent>)
        {
            box_collider_component_pool[id] = std::forward<T>(component);
            signatures[id].set(EComponentType::BoxCollider, true);
        }
    }

    template <typename T>
    T& GetComponent(const EntityId id)
    {
        if constexpr (std::is_same_v<T, CTransformComponent>)
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
        else if constexpr (std::is_same_v<T, CTagComponent>)
        {
            return tag_component_pool[id];
        }
        else if constexpr (std::is_same_v<T, CBoxColliderComponent>)
        {
            return box_collider_component_pool[id];
        }
    }

private:
    uint32 window_width;
    uint32 window_height;

    uint32 score_player1;
    uint32 score_player2;

    float serve_timer;

    uint32 currently_active_entites;
    std::queue<EntityId> available_entity_ids;
    std::vector<Signature> signatures;

    std::vector<CTransformComponent> transform_component_pool;
    std::vector<CVelocityComponent> velocity_component_pool;
    std::vector<CSpriteComponent> sprite_component_pool;
    std::vector<CInputComponent> input_component_pool;
    std::vector<CTagComponent> tag_component_pool;
    std::vector<CBoxColliderComponent> box_collider_component_pool;
};

#endif // WORLD_H
