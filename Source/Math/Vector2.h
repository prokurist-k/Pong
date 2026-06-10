#ifndef VECTOR2_H
#define VECTOR2_H

#include <string>

class CVector2
{
public:
    union
    {
        struct
        {
            float x;
            float y;
        };

        float xy[2];
    };

    static const CVector2 zero_vector;

    static float DistanceSquared(const CVector2& vec1, const CVector2& vec2);
    static float Distance(const CVector2& vec1, const CVector2& vec2);

    CVector2() = default;
    CVector2(float in_x, float in_y);
    CVector2(float in_value);
    CVector2(const CVector2& in_vec);

    const std::string ToString() const;

    CVector2 operator+(const CVector2& vec) const;
    CVector2 operator-(const CVector2& vec) const;
    CVector2 operator*(const float scale) const;
    CVector2 operator/(const float divider) const;
    CVector2 operator+(const float addend) const;
    CVector2 operator-(const float subtrahend) const;

    bool operator==(const CVector2& vec) const;
    bool operator!=(const CVector2& vec) const;

    CVector2 operator-() const;

    CVector2 operator+=(const CVector2& vec);
    CVector2 operator-=(const CVector2& vec);
    CVector2 operator*=(const float factor);
    CVector2 operator/=(const float divider);

    float LengthSquared() const;
    float Length() const;

    float ScalarProduct(const CVector2& vec) const;
    float PseudoCrossProduct(const CVector2& other) const;

    bool Normalize();

    bool IsCollinearTo(const CVector2& vec) const;
    bool IsOrthogonalTo(const CVector2& vec) const;
};

#endif // VECTOR2_H
