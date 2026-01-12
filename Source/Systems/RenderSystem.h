#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "ECS/World.h"
class CRenderSystem
{
public:
    CRenderSystem(class SDL_Renderer* in_renderer);

    void Update(CWorld& world);

private:
    class SDL_Renderer* renderer = nullptr;
};

#endif // RENDERSYSTEM_H
