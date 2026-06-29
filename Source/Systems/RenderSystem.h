#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "ECS/World.h"
class CRenderSystem
{
public:
    CRenderSystem(class SDL_Renderer* in_renderer);

    class SDL_Renderer* GetRenderer()
    {
        return renderer;
    }

    void Update(CWorld& world);

    uint32 GetDrawCalls() const
    {
        return draw_calls;
    }

private:
    class SDL_Renderer* renderer = nullptr;
    uint32 draw_calls = 0;
};

#endif // RENDERSYSTEM_H
