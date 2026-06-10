#include "InputSystem.h"
#include "Components/Components.h"
#include "ECS/Entity.h"
#include "Math/Vector2.h"
#include <SDL_keyboard.h>

CInputSystem::CInputSystem()
{
}

void CInputSystem::Update(CWorld& world)
{
    const Uint8* keyboard_state = SDL_GetKeyboardState(nullptr);

    for (EntityId id = 0; id != MAX_ENTITIES; ++id)
    {
        if (!world.HasComponent(id, EComponentType::Input) || !world.HasComponent(id, EComponentType::Velocity))
        {
            continue;
        }

        CInputComponent& input_component = world.GetComponent<CInputComponent>(id);
        CVelocityComponent& velocity_component = world.GetComponent<CVelocityComponent>(id);

        velocity_component.direction = CVector2::zero_vector;
        velocity_component.speed = 0.0f;

        if (keyboard_state[input_component.key_up])
        {
            velocity_component.direction = CVector2(0.0f, -1.0f);
            velocity_component.speed = input_component.paddle_speed;
        }
        else if (keyboard_state[input_component.key_down])
        {
            velocity_component.direction = CVector2(0.0f, 1.0f);
            velocity_component.speed = input_component.paddle_speed;
        }
    }
}
