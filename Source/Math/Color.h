#ifndef COLOR_H
#define COLOR_H

#include "CoreTypes.h"
#include "Math.h"

#include <format>

class CLinearColor
{
public:
	union
	{
		struct
		{
			float r;
			float g;
			float b;
			float a;
		};

		float rgba[4];
	};

	//CLinearColor() = default;

	CLinearColor()
		: r(0.0f)
		, g(0.0f)
		, b(0.0f)
		, a(0.0f)
	{

	}

	CLinearColor(float value)
		: r(value)
		, g(value)
		, b(value)
		, a(value)
	{
	}

	CLinearColor(float in_r, float in_g, float in_b, float in_a)
		: r(in_r)
		, g(in_g)
		, b(in_b)
		, a(in_a)
	{

	}


	static const CLinearColor black;// { 0.0f, 0.0f, 0.0f, 1.0f };
	static const CLinearColor white;// { 1.0f, 1.0f, 1.0f, 1.0f };

	FORCEINLINE bool operator==(const CLinearColor& color)
	{
		return r == color.r && g == color.g && b == color.b && a == color.a;
	}

	FORCEINLINE bool operator!=(const CLinearColor& color)
	{
		return !(*this == color);
	}

	FORCEINLINE CLinearColor operator+(const CLinearColor& color)
	{
		return CLinearColor(r + color.r, g + color.g, b + color.b, a + color.a);
	}

	FORCEINLINE CLinearColor& operator+=(const CLinearColor& color)
	{
		r += color.r;
		g += color.g;
		b += color.b;
		a += color.a;

		return *this;
	}

	FORCEINLINE CLinearColor operator-(const CLinearColor& color)
	{
		return CLinearColor(r - color.r, g - color.g, b - color.b, a - color.a);
	}

	FORCEINLINE CLinearColor& operator-=(const CLinearColor& color)
	{
		r -= color.r;
		g -= color.g;
		b -= color.b;
		a -= color.a;

		return *this;
	}

	FORCEINLINE CLinearColor operator*(const CLinearColor& color)
	{
		return CLinearColor(r * color.r, g * color.g, b * color.b, a * color.a);
	}

	FORCEINLINE CLinearColor& operator*=(const CLinearColor& color)
	{
		r *= color.r;
		g *= color.g;
		b *= color.b;
		a *= color.a;

		return *this;
	}

	FORCEINLINE CLinearColor operator*(const float factor)
	{
		return CLinearColor(r * factor, g * factor, b * factor, a * factor);
	}

	FORCEINLINE CLinearColor& operator*=(const float factor)
	{
		r *= factor;
		g *= factor;
		b *= factor;
		a *= factor;

		return *this;
	}

	FORCEINLINE CLinearColor operator/(const CLinearColor& color)
	{
		return CLinearColor(r / color.r, g / color.g, b / color.b, a / color.a);
	}

	FORCEINLINE CLinearColor& operator/=(const CLinearColor& color)
	{
		r /= color.r;
		g /= color.g;
		b /= color.b;
		a /= color.a;

		return *this;
	}

	FORCEINLINE CLinearColor operator/(const float scalar)
	{
		return CLinearColor(r / scalar, g / scalar, b / scalar, a / scalar);
	}

	FORCEINLINE CLinearColor& operator/=(const float scalar)
	{
		r /= scalar;
		g /= scalar;
		b /= scalar;
		a /= scalar;

		return *this;
	}

	FORCEINLINE CLinearColor GetClampedColor(float min = 0.0f, float max = 0.0f)
	{
		CLinearColor clamped_color;

		clamped_color.r = CMath::Clamp<float>(r, min, max);
		clamped_color.g = CMath::Clamp<float>(g, min, max);
		clamped_color.b = CMath::Clamp<float>(b, min, max);
		clamped_color.a = CMath::Clamp<float>(a, min, max);

		return clamped_color;
	}

	FORCEINLINE const std::string ToString() const
	{
		return std::format("({}, {}, {}, {})", r, g, b, a);
	}
};

#endif // COLOR_H
