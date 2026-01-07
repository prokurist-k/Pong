#ifndef AABB_H
#define AABB_H

#include "Math/Vector2.h"

static bool CheckAABB(const CVector2& position_a, const CVector2& size_a, const CVector2& position_b, const CVector2& size_b)
{
    if((position_a.x + size_a.x) < position_b.x ) return false;
    if((position_a.x > position_b.x + size_b.x)) return false;
    if((position_a.y + size_a.y < position_b.y)) return false;
    if((position_a.y > position_b.y + size_b.y)) return false;
    return true;
}

#endif // AABB_H
