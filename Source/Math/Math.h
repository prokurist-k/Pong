#ifndef MATH_H
#define MATH_H

#include <math.h>

class CMath
{
public:
    static const float PI;
    static const float TWO_PI;
    static const float HALF_PI;
    static const float INV_PI;
    static const float SQRT_TWO;
    static const float SQRT_THREE;

    static const float RAD2DEG;
    static const float DEG2RAD;

    static const float EPSILON_FLOAT;
    static const double EPSILON_DOUBLE;

    static bool IsNearlyEqual(float a, float b, float tolerance = EPSILON_FLOAT)
    {
        return Abs(a - b) <= tolerance;
    }

    static bool IsNearlyEqual(double a, double b, double tolerance = EPSILON_DOUBLE)
    {
        return Abs(a - b) <= tolerance;
    }

    static bool IsNearlyZero(float a, float tolerance = EPSILON_FLOAT)
    {
        return IsNearlyEqual(a, 0.0f, EPSILON_FLOAT);
    }

    static bool IsNearlyZero(double a, double tolerance = EPSILON_DOUBLE)
    {
        return IsNearlyEqual(a, 0.0, EPSILON_DOUBLE);
    }

    template <typename T>
    static T Min(const T a, const T b)
    {
        return (a < b) ? a : b;
    }

    template <typename T>
    static T Max(const T a, const T b)
    {
        return (a > b) ? a : b;
    }

    template <typename T>
    static T Clamp(T value, T min, T max)
    {
        return Min(Max(value, min), max);
    }

    static float Abs(const float value)
    {
        return fabsf(value);
    }
    static double Abs(const double value)
    {
        return fabs(value);
    }

    static float Pow(float base, float exponent)
    {
        return powf(base, exponent);
    }
    static double Pow(double base, double exponent)
    {
        return pow(base, exponent);
    }

    static float Sqrt(float radicand)
    {
        if (radicand < 0.f)
        {
            // HADES_LOG(Warning, "Sqrt called with negative
            // value: %f", radicand)
            return NAN;
        }
        return sqrtf(radicand);
    }

    static double Sqrt(double radicand)
    {
        if (radicand < 0.f)
        {
            // HADES_LOG(Warning, "Sqrt called with negative
            // value: %d", radicand)
            return NAN;
        }
        return sqrt(radicand);
    }

    static float InvSqrt(float radicand)
    {
        return 1.f / sqrtf(radicand);
    }
    static double InvSqrt(double radicand)
    {
        return 1.f / sqrt(radicand);
    }

    static float Exp(float exponent)
    {
        return expf(exponent);
    }
    static double Exp(double exponent)
    {
        return exp(exponent);
    }
    static float Exp2(float exponent)
    {
        return exp2f(exponent);
    }
    static double Exp2(double exponent)
    {
        return exp2(exponent);
    }

    static float LogE(float x)
    {
        return logf(x);
    }
    static double LogE(double x)
    {
        return log(x);
    }
    static float LogX(float base, float value)
    {
        return LogE(value) / LogE(base);
    }
    static double LogX(double base, double value)
    {
        return LogE(value) / LogE(base);
    }

    static float Sin(float x)
    {
        return sinf(x);
    }
    static double Sin(double x)
    {
        return sin(x);
    }

    static float ASin(float x)
    {
        return asinf(Clamp<float>(x, -1.f, 1.f));
    }
    static double ASin(double x)
    {
        return asin(Clamp<double>(x, -1., 1.));
    }

    static float Cos(float x)
    {
        return cosf(x);
    }
    static double Cos(double x)
    {
        return cos(x);
    }

    static float ACos(float x)
    {
        return acosf(x);
    }
    static double ACos(double x)
    {
        return acos(x);
    }

    static float Tan(float x)
    {
        return tanf(x);
    }
    static double Tan(double x)
    {
        return tan(x);
    }

    static float ATan(float x)
    {
        return atanf(x);
    }
    static double ATan(double x)
    {
        return atan(x);
    }
};

#endif // MATH_H
