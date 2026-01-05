#ifndef RENDERSYSTEM_J
#define RENDERSYSTEM_J

#include "ECS/World.h"
class CRenderSystem
{
public:
    CRenderSystem(class SDL_Renderer* in_renderer);

    void Update(CWorld& world);

private:
    class SDL_Renderer* renderer = nullptr;
};

#endif // RENDERSYSTEM_J
