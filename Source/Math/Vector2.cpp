#include "Vector2.h"
#include "Math.h"

#include <format>

/*static*/ const CVector2 CVector2::zero_vector = CVector2(0.0f, 0.0f);

	/*static*/ float CVector2::DistanceSquared(const CVector2& vec1, const CVector2& vec2)
	{
		return CMath::Pow(vec2.x - vec1.x, 2.f) + CMath::Pow(vec2.y - vec1.y, 2.f);
	}

	/*static*/ float CVector2::Distance(const CVector2& vec1, const CVector2& vec2)
	{
		return CMath::Sqrt(DistanceSquared(vec1, vec2));
	}

	CVector2::CVector2(float in_x, float in_y)
		: x(in_x)
		, y(in_y)
	{

	}

	CVector2::CVector2(float in_value)
		: x(in_value)
		, y(in_value)
	{

	}

	CVector2::CVector2(const CVector2& in_vec)
		: x(in_vec.x)
		, y(in_vec.y)
	{

	}

	CVector2 CVector2::operator+(const CVector2& vec) const
	{
		return CVector2(x + vec.x, y + vec.y);
	}

	CVector2 CVector2::operator-(const CVector2& vec) const
	{
		return CVector2(x - vec.x, y - vec.y);
	}

	CVector2 CVector2::operator*(const float scale) const
	{
		return CVector2(x * scale, y * scale);
	}

	CVector2 CVector2::operator/(const float divider) const
	{
		//HADES_ASSERT(divider != 0, "division by 0")
		const float inverse = 1.0f / divider;
		return CVector2(x * inverse, y * inverse);
	}

	CVector2 CVector2::operator+(const float addend) const
	{
		return CVector2(x + addend, y + addend);
	}

	CVector2 CVector2::operator-(const float subtrahend) const
	{
		return CVector2(x - subtrahend, y - subtrahend);
	}

	bool CVector2::operator==(const CVector2& vec) const
	{
		return ((x == vec.x) && (y == vec.y));
	}

	bool CVector2::operator!=(const CVector2& vec) const
	{
		return !(*this == vec);
	}

	CVector2 CVector2::operator-() const
	{
		return CVector2(-x, -y);
	}

	CVector2 CVector2::operator+=(const CVector2& vec)
	{
		x += vec.x;
		y += vec.y;
		return *this;
	}

	CVector2 CVector2::operator-=(const CVector2& vec)
	{
		x -= vec.x;
		y -= vec.y;
		return *this;
	}

	CVector2 CVector2::operator*=(const float factor)
	{
		x *= factor;
		y *= factor;
		return *this;
	}

	CVector2 CVector2::operator/=(const float divider)
	{
		//HADES_ASSERT(divider != 0, "division by 0")
		const float inverse = 1.0f / divider;
		x *= inverse;
		y *= inverse;

		return *this;
	}

	float CVector2::LengthSquared() const
	{
		return x * x + y * y;
	}

	float CVector2::Length() const
	{
		return CMath::Sqrt(LengthSquared());
	}

	float CVector2::ScalarProduct(const CVector2& vec) const
	{
		return x * vec.x + y * vec.y;
	}

	float CVector2::PseudoCrossProduct(const CVector2& other) const
	{
		return x * other.y - y * other.x;
	}

	bool CVector2::Normalize()
	{
		const float length = Length();
		if (length > 0.f)
		{
			*this /= length;
			return true;
		}
		return false;
	}

	bool CVector2::IsCollinearTo(const CVector2& vec) const
	{
		if (vec == zero_vector || *this == zero_vector)
		{
			return true;
		}

		float cross_product = PseudoCrossProduct(vec);
		return CMath::IsNearlyZero(cross_product);
	}

	bool CVector2::IsOrthogonalTo(const CVector2& vec) const
	{
		const float scalar_product = ScalarProduct(vec);
		return CMath::IsNearlyZero(scalar_product);
	}

	const std::string CVector2::ToString() const
	{
		return std::format("({}, {})", x, y);
	}
