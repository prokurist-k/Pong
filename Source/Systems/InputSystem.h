#ifndef INPUT_SYSTEM_H
#define INPUT_SYSTEM_H

#include "ECS/World.h"
class CInputSystem
{
public:
    CInputSystem();

    void Update(CWorld& world);
};

#endif // INPUT_SYSTEM_H
