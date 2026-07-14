#include "RenderSystem.h"
#include "Math/Color.h"
#include "Math/Vector2.h"
#include <SDL_log.h>

#include <SDL_render.h>
#include <cstdlib>
#include <vector>

CRenderSystem::CRenderSystem(SDL_Renderer* in_renderer)
    : renderer(in_renderer)
{
}

void CRenderSystem::Update(CWorld& world)
{
    for (auto& pair : color_groups)
    {
        pair.second.clear();
    }

    draw_calls = 0;
    for (EntityId id : world.GetActiveEntitesForRendering())
    {
        if (!world.HasComponent(id, EComponentType::Transform) || !world.HasComponent(id, EComponentType::Sprite))
        {
            continue;
        }

        CTransformComponent transform_component = world.GetComponent<CTransformComponent>(id);
        CSpriteComponent sprite_component = world.GetComponent<CSpriteComponent>(id);

        SDL_Rect rect;
        rect.x = static_cast<int32>(transform_component.location.x);
        rect.y = static_cast<int32>(transform_component.location.y);
        rect.w = static_cast<int32>(transform_component.scale.x);
        rect.h = static_cast<int32>(transform_component.scale.y);

        const uint32 color_code = sprite_component.color.ToUint32();
        color_groups[color_code].emplace_back(rect);
    }

    for (auto& pair : color_groups)
    {
        const std::vector<SDL_Rect>& batch = pair.second;
        if (batch.empty())
            continue;

        CColor color = CColor::FromUint32(pair.first);

        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderFillRects(renderer, pair.second.data(), static_cast<int32>(pair.second.size()));
        draw_calls++;
    }
}

void CRenderSystem::UpdateCameraShake(float delta_seconds)
{
    if (camera_shake_timer > 0.0f)
    {
        camera_shake_timer -= delta_seconds;

        camera_shake_offset.x = (rand() % 200 - 100) / 100.0f * camera_shake_intesity;
        camera_shake_offset.y = (rand() % 200 - 100) / 100.0f * camera_shake_intesity;

        camera_shake_intesity *= 0.9f;
    }
    else
    {
        camera_shake_offset - CVector2::zero_vector;
    }
}
