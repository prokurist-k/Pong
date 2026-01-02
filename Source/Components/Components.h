#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "CoreTypes.h"
#include "Math/Color.h"
#include "Math/Vector2.h"

#include <bitset>

const uint32 MAX_COMPONENTS = 32;
using Signature = std::bitset<MAX_COMPONENTS>;

enum EComponentType
{
    Transform = 0,
    Velocity,
    Sprite,
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

    CVector2 direction = CVector2::zero_vector;
    float speed = 0.0f;
};

class CSpriteComponent
{
public:
    CSpriteComponent() = default;
    CSpriteComponent(const CLinearColor& in_color)
        : color(in_color)
    {}

    CLinearColor color;
};

#endif // COMPONENTS_H
