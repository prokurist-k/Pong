#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "ECS/World.h"
#include "Math/Vector2.h"
#include <SDL_rect.h>
#include <map>
#include <vector>

class CRenderSystem
{
public:
    CRenderSystem(class SDL_Renderer* in_renderer);

    class SDL_Renderer* GetRenderer()
    {
        return renderer;
    }

    void Update(CWorld& world);
    void UpdateCameraShake(float delta_seconds);

    uint32 GetDrawCalls() const
    {
        return draw_calls;
    }

private:
    class SDL_Renderer* renderer = nullptr;
    uint32 draw_calls = 0;

    std::map<uint32, std::vector<SDL_Rect>> color_groups;

    float camera_shake_timer = 0.0f;
    float camera_shake_intesity = 0.0f;
    CVector2 camera_shake_offset = CVector2::zero_vector;
};

#endif // RENDERSYSTEM_H
