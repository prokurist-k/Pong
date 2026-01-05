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

	CLinearColor()
		: r(0.0f)
		, g(0.0f)
		, b(0.0f)
		, a(0.0f)
	{

	}

	CLinearColor(float in_value)
		: r(in_value)
		, g(in_value)
		, b(in_value)
		, a(1.0f)
	{
	}

	CLinearColor(float in_r, float in_g, float in_b, float in_a)
		: r(in_r)
		, g(in_g)
		, b(in_b)
		, a(in_a)
	{

	}


	static const CLinearColor black;
	static const CLinearColor white;

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

class CColor
{
public:
	union
	{
		struct
		{
			uint32 r;
			uint32 g;
			uint32 b;
			uint32 a;
		};

		uint32 rgba[4];
	};

	CColor()
		: r(0)
		, g(0)
		, b(0)
		, a(0)
	{

	}

	CColor(uint32 in_value)
		: r(in_value)
		, g(in_value)
		, b(in_value)
		, a(255)
	{
	}

	CColor(uint32 in_r, uint32 in_g, uint32 in_b, uint32 in_a)
		: r(in_r)
		, g(in_g)
		, b(in_b)
		, a(in_a)
	{

	}


	static const CColor black;
	static const CColor white;

	FORCEINLINE CLinearColor ToLinearColor() const
	{
	    return CLinearColor(r * 255, g * 255, b * 255, a * 255);
	}

	FORCEINLINE bool operator==(const CColor& color)
	{
		return r == color.r && g == color.g && b == color.b && a == color.a;
	}

	FORCEINLINE bool operator!=(const CColor& color)
	{
		return !(*this == color);
	}

	FORCEINLINE CColor operator+(const CColor& color)
	{
		return CColor(r + color.r, g + color.g, b + color.b, a + color.a);
	}

	FORCEINLINE CColor& operator+=(const CColor& color)
	{
		r += color.r;
		g += color.g;
		b += color.b;
		a += color.a;

		return *this;
	}

	FORCEINLINE CColor operator-(const CColor& color)
	{
		return CColor(r - color.r, g - color.g, b - color.b, a - color.a);
	}

	FORCEINLINE CColor& operator-=(const CColor& color)
	{
		r -= color.r;
		g -= color.g;
		b -= color.b;
		a -= color.a;

		return *this;
	}

	FORCEINLINE CColor operator*(const CColor& color)
	{
		return CColor(r * color.r, g * color.g, b * color.b, a * color.a);
	}

	FORCEINLINE CColor& operator*=(const CColor& color)
	{
		r *= color.r;
		g *= color.g;
		b *= color.b;
		a *= color.a;

		return *this;
	}

	FORCEINLINE CColor operator*(const float factor)
	{
		return CColor(r * factor, g * factor, b * factor, a * factor);
	}

	FORCEINLINE CColor& operator*=(const float factor)
	{
		r *= factor;
		g *= factor;
		b *= factor;
		a *= factor;

		return *this;
	}

	FORCEINLINE CColor operator/(const CColor& color)
	{
		return CColor(r / color.r, g / color.g, b / color.b, a / color.a);
	}

	FORCEINLINE CColor& operator/=(const CColor& color)
	{
		r /= color.r;
		g /= color.g;
		b /= color.b;
		a /= color.a;

		return *this;
	}

	FORCEINLINE CColor operator/(const float scalar)
	{
		return CColor(r / scalar, g / scalar, b / scalar, a / scalar);
	}

	FORCEINLINE CColor& operator/=(const float scalar)
	{
		r /= scalar;
		g /= scalar;
		b /= scalar;
		a /= scalar;

		return *this;
	}

	FORCEINLINE CColor GetClampedColor(uint32 min = 0.0f, uint32 max = 0.0f)
	{
		CColor clamped_color;

		clamped_color.r = CMath::Clamp<uint32>(r, min, max);
		clamped_color.g = CMath::Clamp<uint32>(g, min, max);
		clamped_color.b = CMath::Clamp<uint32>(b, min, max);
		clamped_color.a = CMath::Clamp<uint32>(a, min, max);

		return clamped_color;
	}

	FORCEINLINE const std::string ToString() const
	{
		return std::format("({}, {}, {}, {})", r, g, b, a);
	}
};

#endif // COLOR_H
