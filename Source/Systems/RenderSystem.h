#ifndef RENDERSYSTEM_J
#define RENDERSYSTEM_J

#include "ECS/World.h"
#include <SDL_render.h>
class CRenderSystem
{
public:
    CRenderSystem(SDL_Renderer* in_renderer);

    void Update(CWorld& world);

private:
    SDL_Renderer* renderer = nullptr;
};

#endif // RENDERSYSTEM_J
