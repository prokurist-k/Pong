#include "RenderSystem.h"
#include "Components/Components.h"
#include "ECS/Entity.h"
#include <SDL_rect.h>
#include <SDL_render.h>

CRenderSystem::CRenderSystem(SDL_Renderer* in_renderer)
    : renderer(in_renderer)
{
}

void CRenderSystem::Update(CWorld& world)
{
    draw_calls = 0;
    for (EntityId id = 0; id != MAX_ENTITIES; ++id)
    {
        if (!world.HasComponent(id, EComponentType::Transform) || !world.HasComponent(id, EComponentType::Sprite))
        {
            continue;
        }

        CTransformComponent transform_component = world.GetComponent<CTransformComponent>(id);
        CSpriteComponent sprite_component = world.GetComponent<CSpriteComponent>(id);

        SDL_Rect rect;
        rect.x = static_cast<int>(transform_component.location.x);
        rect.y = static_cast<int>(transform_component.location.y);
        rect.w = static_cast<int>(transform_component.scale.x);
        rect.h = static_cast<int>(transform_component.scale.y);

        SDL_SetRenderDrawColor(renderer, sprite_component.color.r, sprite_component.color.g, sprite_component.color.b, sprite_component.color.a);
        SDL_RenderFillRect(renderer, &rect);
        draw_calls++;
    }
}
