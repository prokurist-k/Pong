#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "CoreTypes.h"
#include "Math/Color.h"
#include "Math/Vector2.h"

#include <SDL_scancode.h>
#include <bitset>

const uint32 MAX_COMPONENTS = 32;
using Signature = std::bitset<MAX_COMPONENTS>;

enum EComponentType
{
    Transform = 0,
    Velocity,
    Sprite,
    Input,
    MaxComponents
};


class CTransformComponent
{
public:

    CTransformComponent() = default;
    CTransformComponent(const CVector2& in_location, const float in_angle = 0.0f, const CVector2& in_scale = CVector2(1.0f))
     : location(in_location)
     , angle(in_angle)
     , scale(in_scale)
    {

    }

    CVector2 location;
    float angle;
    CVector2 scale;
};

class CVelocityComponent
{
public:
    CVelocityComponent() = default;
    CVelocityComponent(const CVector2& in_direction, float in_speed)
        : direction(in_direction)
        , speed(in_speed)
    {

    }

    CVector2 direction = CVector2::zero_vector;
    float speed = 0.0f;
};

class CSpriteComponent
{
public:
    CSpriteComponent() = default;
    CSpriteComponent(const CColor& in_color)
        : color(in_color)
    {}

    CColor color;
};

class CInputComponent
{
public:
    CInputComponent() = default;
    CInputComponent(SDL_Scancode in_key_up, SDL_Scancode in_key_down, float in_paddle_speed)
        : key_up(in_key_up)
        , key_down(in_key_down)
        , paddle_speed(in_paddle_speed)
    {

    }

    SDL_Scancode key_up;
    SDL_Scancode key_down;
    float paddle_speed;
};

#endif // COMPONENTS_H
