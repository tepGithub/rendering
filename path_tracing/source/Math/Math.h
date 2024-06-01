#pragma once

#include "Numbers.h"
#include <cmath>
#include <cstdint>

namespace Math
{
	// if (s>=0) return x; else return y; New hardware has functions to avoid branching
	inline float fsel(float t, float x, float y)
	{
		return (t >= 0.0f) ? x : y;
	}

	inline float rcp(float f)
	{
		return 1.0f / f;
	}

	inline float min(const float& f1, const float& f2)
	{
		// fsel((f2 - f1), f1, f2);
		return (f1 <= f2) ? f1 : f2;
	}

	inline float max(float f1, float f2)
	{
		// fsel((f1 - f2), f1, f2)
		return (f1 >= f2) ? f1 : f2;
	}

	inline float clamp(float f, float _fmin, float _fmax)
	{
		return min(max(f, _fmin), _fmax);
	}

	inline float saturate(float f)
	{
		return clamp(f, 0.0f, 1.0f);
	}

	inline float frac(float f)
	{
		return f - floorf(f);
	}

	// converts from degrees to radians
	constexpr float radians(float deg)
	{
		return	(deg * Math::pif / 180.0f);
	}

	// converts from radians to degrees.
	constexpr float degrees(float rad)
	{
		return (rad * 180.0f / Math::pif);
	}

	template <typename T>
	inline T lerp(const T& a, const T& b, float t)
	{
		return a + ((b - a) * t);
	}

	template <typename T>
	inline T smoothstep(const T& a, const T& b, float t)
	{
		t = saturate((t - a) / (b - a));
		return t * t * (3.0f - 2.0f * t);
	}

	template <typename T>
	inline T barycentric(const T& a, const T& b, const T& c, float f, float g)
	{
		// B(f,g) = (1-f-g)*a + f*b + g*c
		return (1 - f - g) * a + f * b + g * c;
	}

	template <typename T>
	inline T catmullrom(const T& v0, const T& v1, const T& v2, const T& v3, float t)
	{
		float t2 = t * t;
		float t3 = t2 * t;

		float P0 = -t3 + 2.0f * t2 - t;
		float P1 = 3.0f * t3 - 5.0f * t2 + 2.0f;
		float P2 = -3.0f * t3 + 4.0f * t2 + t;
		float P3 = t3 - t2;

		return (P0 * v0 + P1 * v1 + P2 * v2 + P3 * v3) * 0.5f;
	}

	template <typename T>
	inline T hermite(const T& v0, const T& t0, const T& v1, const T& t1, float t)
	{
		float t2 = t * t;
		float t3 = t2 * t;

		float P0 = 2.0f * t3 - 3.0f * t2 + 1.0f;
		float T0 = t3 - 2.0f * t2 + t;
		float P1 = -2.0f * t3 + 3.0f * t2;
		float T1 = t3 - t2;

		return P0 * v0 + T0 * t0 + P1 * v1 + T1 * t1;
	}

	inline float u8tof32(uint8_t i)
	{
		return i / 255.0f;
	}

	inline float u16tof32(uint16_t i)
	{
		return i / 65535.0f;
	}

	inline uint8_t f32tou8(float f)
	{
		return static_cast<uint8_t>(saturate(f) * 255.0f);
	}

	inline uint16_t f32tou16(float f)
	{
		return static_cast<uint16_t>(saturate(f) * 65535.0f);
	}
}