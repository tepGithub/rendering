#pragma once

#include "Math.h"

namespace Math
{
	// Forward declarations
	template <class T, int Dim> struct vec;
	template <class T> using vec2 = vec<T, 2>;
	template <class T> using vec3 = vec<T, 3>;
	template <class T> using vec4 = vec<T, 4>;
	
	// scalar
	using byte = unsigned char;
	using uint = unsigned int;

	// vector
	template <class T>
	struct vec<T, 2>
	{
		static constexpr uint kDimension = 2;

		using scalar_type = T;
		union
		{
			T m_data[kDimension];
			struct { T x, y; };
		};

		// Constructors
		vec() {}
		constexpr vec(T _x) : m_data{ _x, _x } {}
		constexpr vec(T _x, T _y) : m_data{ _x, _y } {}
		constexpr vec(const vec& other) : m_data{ other[0], other[1] } {}
		constexpr vec(const T(&other)[2]) : m_data{ other[0], other[1] } {}

		// Array operators
		constexpr T&        operator[] (uint i) { return m_data[i]; }
		constexpr const T&  operator[] (uint i) const { return m_data[i]; }
		constexpr T*        begin() { return m_data; }
		constexpr const T*  begin() const { return m_data; }
		constexpr T*        end() { return (m_data + kDimension); }
		constexpr const T*  end() const { return (m_data + kDimension); }

		// Assignment operators
		constexpr vec& operator =(const vec& other) { m_data[0] = other[0]; m_data[1] = other[1]; return *this; }
		constexpr vec& operator+=(const vec& other) { m_data[0] += other[0]; m_data[1] += other[1]; return *this; }
		constexpr vec& operator-=(const vec& other) { m_data[0] -= other[0]; m_data[1] -= other[1]; return *this; }
		constexpr vec& operator*=(const vec& other) { m_data[0] *= other[0]; m_data[1] *= other[1]; return *this; }
		constexpr vec& operator/=(const vec& other) { m_data[0] /= other[0]; m_data[1] /= other[1]; return *this; }
		//constexpr vec& operator%=(const vec& other) { m_data[0] %= other[0]; m_data[1] %= other[1]; return *this; }

		// Unary operators
		constexpr vec& operator +() { return *this; }		
		constexpr vec  operator -() { return vec(-m_data[0], -m_data[1]); }
		//constexpr vec  operator !() { return vec(!m_data[0], !m_data[1]); }
		//constexpr vec  operator ~() { return vec(~m_data[0], ~m_data[1]); }

		// Conversion operators
		constexpr explicit operator vec<int, kDimension>() const { return vec<int, kDimension>(static_cast<int>(m_data[0]), static_cast<int>(m_data[1])); }
		constexpr explicit operator vec<uint, kDimension>() const { return vec<uint, kDimension>(static_cast<uint>(m_data[0]), static_cast<uint>(m_data[1])); }

		// Constants
		static constexpr vec zero() { return vec(0); }
		static constexpr vec one() { return vec(1); }
	};

	// Arithmetic binary operators (+, -, *, /, %)
	template <class T> constexpr auto operator +(const vec<T, 2>& lhs, const vec<T, 2>& rhs) { return vec<T, 2>(lhs[0] + rhs[0], lhs[1] + rhs[1]); }
	template <class T> constexpr auto operator +(T                lhs, const vec<T, 2>& rhs) { return vec<T, 2>(lhs    + rhs[0], lhs    + rhs[1]); }
	template <class T> constexpr auto operator +(const vec<T, 2>& lhs, T                rhs) { return vec<T, 2>(lhs[0] + rhs   , lhs[1] + rhs   ); }
	template <class T> constexpr auto operator -(const vec<T, 2>& lhs, const vec<T, 2>& rhs) { return vec<T, 2>(lhs[0] - rhs[0], lhs[1] - rhs[1]); }
	template <class T> constexpr auto operator -(T                lhs, const vec<T, 2>& rhs) { return vec<T, 2>(lhs    - rhs[0], lhs    - rhs[1]); }
	template <class T> constexpr auto operator -(const vec<T, 2>& lhs, T                rhs) { return vec<T, 2>(lhs[0] - rhs   , lhs[1] - rhs   ); }
	template <class T> constexpr auto operator *(const vec<T, 2>& lhs, const vec<T, 2>& rhs) { return vec<T, 2>(lhs[0] * rhs[0], lhs[1] * rhs[1]); }
	template <class T> constexpr auto operator *(T                lhs, const vec<T, 2>& rhs) { return vec<T, 2>(lhs    * rhs[0], lhs    * rhs[1]); }
	template <class T> constexpr auto operator *(const vec<T, 2>& lhs, T                rhs) { return vec<T, 2>(lhs[0] * rhs   , lhs[1] * rhs   ); }
	template <class T> constexpr auto operator /(const vec<T, 2>& lhs, const vec<T, 2>& rhs) { return vec<T, 2>(lhs[0] / rhs[0], lhs[1] / rhs[1]); }
	template <class T> constexpr auto operator /(T                lhs, const vec<T, 2>& rhs) { return vec<T, 2>(lhs    / rhs[0], lhs    / rhs[1]); }
	template <class T> constexpr auto operator /(const vec<T, 2>& lhs, T                rhs) { return vec<T, 2>(lhs[0] / rhs   , lhs[1] / rhs   ); }

	// Relational binary operators (==, !=)
	template <class T> constexpr bool operator==(const vec<T, 2>& lhs, const vec<T, 2>& rhs) { return lhs[0] == rhs[0] && lhs[1] == rhs[1]; }
	template <class T> constexpr bool operator!=(const vec<T, 2>& lhs, const vec<T, 2>& rhs) { return lhs[0] != rhs[0] || lhs[1] != rhs[1]; }

	template <class T>
	struct vec<T, 3>
	{
		static constexpr uint kDimension = 3;

		using scalar_type = T;
		union
		{
			T m_data[kDimension];
			struct { T x, y, z; };
		};

		// Constructors
		vec() {}
		constexpr vec(T _x) : m_data{ _x, _x, _x } {}
		constexpr vec(T _x, T _y, T _z) : m_data{ _x, _y, _z } {}
		constexpr vec(const vec& other) : m_data{ other[0], other[1], other[2] } {}
		constexpr vec(const vec<T, 2>& xy, T z) : m_data{ xy[0], xy[1], z } {}
		constexpr vec(const T(&other)[3]) : m_data{ other[0], other[1], other[2] } {}

		// Array operators
		constexpr T&        operator[] (uint i) { return m_data[i]; }
		constexpr const T&  operator[] (uint i) const { return m_data[i]; }
		constexpr T*        begin() { return m_data; }
		constexpr const T*  begin() const { return m_data; }
		constexpr T*        end() { return (m_data + kDimension); }
		constexpr const T*  end() const { return (m_data + kDimension); }

		// Assignment operators
		constexpr vec& operator =(const vec& other) { m_data[0] = other[0]; m_data[1] = other[1]; m_data[2] = other[2]; return *this; }
		constexpr vec& operator+=(const vec& other) { m_data[0] += other[0]; m_data[1] += other[1]; m_data[2] += other[2]; return *this; }
		constexpr vec& operator-=(const vec& other) { m_data[0] -= other[0]; m_data[1] -= other[1]; m_data[2] -= other[2]; return *this; }
		constexpr vec& operator*=(const vec& other) { m_data[0] *= other[0]; m_data[1] *= other[1]; m_data[2] *= other[2]; return *this; }
		constexpr vec& operator/=(const vec& other) { m_data[0] /= other[0]; m_data[1] /= other[1]; m_data[2] /= other[2]; return *this; }
		//constexpr vec& operator%=(const vec& other) { m_data[0] %= other[0]; m_data[1] %= other[1]; m_data[2] %= other[2]; return *this; }

		// Unary operators
		constexpr vec& operator +() { return *this; }
		constexpr vec  operator -() { return vec(-m_data[0], -m_data[1], -m_data[2]); }
        //constexpr vec  operator !() { return vec(!m_data[0], !m_data[1], !m_data[2]); }
		//constexpr vec  operator ~() { return vec(~m_data[0], ~m_data[1], ~m_data[2]); }

		// Conversion operators
		constexpr explicit operator vec<int, kDimension>() const { return vec<int, kDimension>(static_cast<int>(m_data[0]), static_cast<int>(m_data[1]), static_cast<int>(m_data[2])); }
		constexpr explicit operator vec<uint, kDimension>() const { return vec<uint, kDimension>(static_cast<uint>(m_data[0]), static_cast<uint>(m_data[1]), static_cast<uint>(m_data[2])); }

		// Constants
		static constexpr vec zero() { return vec(0); }
		static constexpr vec one() { return vec(1); }
	};

	// Arithmetic binary operators (+, -, *, /, %)
	template <class T> constexpr auto operator +(const vec<T, 3>& lhs, const vec<T, 3>& rhs) { return vec<T, 3>(lhs[0] + rhs[0], lhs[1] + rhs[1], lhs[2] + rhs[2]); }
	template <class T> constexpr auto operator -(const vec<T, 3>& lhs, const vec<T, 3>& rhs) { return vec<T, 3>(lhs[0] - rhs[0], lhs[1] - rhs[1], lhs[2] - rhs[2]); }
	template <class T> constexpr auto operator *(const vec<T, 3>& lhs, const vec<T, 3>& rhs) { return vec<T, 3>(lhs[0] * rhs[0], lhs[1] * rhs[1], lhs[2] * rhs[2]); }
	template <class T> constexpr auto operator *(T                lhs, const vec<T, 3>& rhs) { return vec<T, 3>(lhs    * rhs[0], lhs    * rhs[1], lhs    * rhs[2]); }
	template <class T> constexpr auto operator *(const vec<T, 3>& lhs, T                rhs) { return vec<T, 3>(lhs[0] * rhs   , lhs[1] * rhs   , lhs[2] * rhs   ); }
	template <class T> constexpr auto operator /(const vec<T, 3>& lhs, const vec<T, 3>& rhs) { return vec<T, 3>(lhs[0] / rhs[0], lhs[1] / rhs[1], lhs[2] / rhs[2]); }

	// Relational binary operators (==, !=)
	template <class T> constexpr bool operator==(const vec<T, 3>& lhs, const vec<T, 3>& rhs) { return lhs[0] == rhs[0] && lhs[1] == rhs[1] && lhs[2] == rhs[2]; }
	template <class T> constexpr bool operator!=(const vec<T, 3>& lhs, const vec<T, 3>& rhs) { return lhs[0] != rhs[0] || lhs[1] != rhs[1] || lhs[2] != rhs[2]; }


	template <class T>
	struct vec<T, 4>
	{
		static constexpr uint kDimension = 4;

		using scalar_type = T;
		union
		{
			T m_data[kDimension];
			struct { T x, y, z, w; };
		};

		// Constructors
		vec() {}
		constexpr vec(T _x) : m_data{ _x, _x, _x, _x } {}
		constexpr vec(T _x, T _y, T _z, T _w) : m_data{ _x, _y, _z, _w } {}
		constexpr vec(const vec& other) : m_data{ other[0], other[1], other[2], other[3] } {}
		constexpr vec(const vec<T, 3>& xyz, T w) : m_data{ xyz[0], xyz[1], xyz[2], w } {}
		constexpr vec(const T(&other)[4]) : m_data{ other[0], other[1], other[2], other[3] } {}

		// Array operators
		constexpr T&        operator[] (uint i) { return m_data[i]; }
		constexpr const T&  operator[] (uint i) const { return m_data[i]; }
		constexpr T*        begin() { return m_data; }
		constexpr const T*  begin() const { return m_data; }
		constexpr T*        end() { return (m_data + kDimension); }
		constexpr const T*  end() const { return (m_data + kDimension); }

		// Assignment operators
		constexpr vec& operator =(const vec& other) { m_data[0] = other[0]; m_data[1] = other[1]; m_data[2] = other[2]; m_data[3] = other[3]; return *this; }
		constexpr vec& operator+=(const vec& other) { m_data[0] += other[0]; m_data[1] += other[1]; m_data[2] += other[2]; m_data[3] += other[3]; return *this; }
		constexpr vec& operator-=(const vec& other) { m_data[0] -= other[0]; m_data[1] -= other[1]; m_data[2] -= other[2]; m_data[3] -= other[3]; return *this; }
		constexpr vec& operator*=(const vec& other) { m_data[0] *= other[0]; m_data[1] *= other[1]; m_data[2] *= other[2]; m_data[3] *= other[3]; return *this; }
		constexpr vec& operator/=(const vec& other) { m_data[0] /= other[0]; m_data[1] /= other[1]; m_data[2] /= other[2]; m_data[3] /= other[3]; return *this; }
		//constexpr vec& operator%=(const vec& other) { m_data[0] %= other[0]; m_data[1] %= other[1]; m_data[2] %= other[2]; m_data[3] %= other[3]; return *this; }

		// Unary operators
		constexpr vec& operator +() { return *this; }
		constexpr vec  operator -() { return vec(-m_data[0], -m_data[1], -m_data[2], -m_data[3]); }
		//constexpr vec  operator !() { return vec(!m_data[0], !m_data[1], !m_data[2], !m_data[3]); }
		//constexpr vec  operator ~() { return vec(~m_data[0], ~m_data[1], ~m_data[2], ~m_data[3]); }

		// Conversion operators
		constexpr explicit operator vec<int, kDimension>() const { return vec<int, kDimension>(static_cast<int>(m_data[0]), static_cast<int>(m_data[1]), static_cast<int>(m_data[2]), static_cast<int>(m_data[3])); }
		constexpr explicit operator vec<uint, kDimension>() const { return vec<uint, kDimension>(static_cast<uint>(m_data[0]), static_cast<uint>(m_data[1]), static_cast<uint>(m_data[2]), static_cast<uint>(m_data[3])); }

		// Constants
		static constexpr vec zero() { return vec(0); }
		static constexpr vec one() { return vec(1); }
	};

	// Arithmetic binary operators (+, -, *, /, %)
	template <class T> constexpr auto operator +(const vec<T, 4>& lhs, const vec<T, 4>& rhs) { return vec<T, 4>(lhs[0] + rhs[0], lhs[1] + rhs[1], lhs[2] + rhs[2], lhs[3] + rhs[3]); }
	template <class T> constexpr auto operator -(const vec<T, 4>& lhs, const vec<T, 4>& rhs) { return vec<T, 4>(lhs[0] - rhs[0], lhs[1] - rhs[1], lhs[2] - rhs[2], lhs[3] - rhs[3]); }
	template <class T> constexpr auto operator *(const vec<T, 4>& lhs, const vec<T, 4>& rhs) { return vec<T, 4>(lhs[0] * rhs[0], lhs[1] * rhs[1], lhs[2] * rhs[2], lhs[3] * rhs[3]); }
	template <class T> constexpr auto operator *(T                lhs, const vec<T, 4>& rhs) { return vec<T, 4>(lhs    * rhs[0], lhs    * rhs[1], lhs    * rhs[2], lhs    * rhs[3]); }
	template <class T> constexpr auto operator *(const vec<T, 4>& lhs, T                rhs) { return vec<T, 4>(lhs[0] * rhs   , lhs[1] * rhs   , lhs[2] * rhs   , lhs[3] * rhs   ); }
	template <class T> constexpr auto operator /(const vec<T, 4>& lhs, const vec<T, 4>& rhs) { return vec<T, 4>(lhs[0] / rhs[0], lhs[1] / rhs[1], lhs[2] / rhs[2], lhs[3] / rhs[3]); }

	// Relational binary operators (==, !=)
	template <class T> constexpr bool operator==(const vec<T, 4>& lhs, const vec<T, 4>& rhs) { return lhs[0] == rhs[0] && lhs[1] == rhs[1] && lhs[2] == rhs[2] && lhs[3] == rhs[3]; }
	template <class T> constexpr bool operator!=(const vec<T, 4>& lhs, const vec<T, 4>& rhs) { return lhs[0] != rhs[0] || lhs[1] != rhs[1] || lhs[2] != rhs[2] || lhs[3] != rhs[3]; }

	// Aliases

	// float
	using float2 = vec2<float>;
	using float3 = vec3<float>;
	using float4 = vec4<float>;

	// double
	using double2 = vec2<double>;
	using double3 = vec3<double>;
	using double4 = vec4<double>;

	// int
	using int2 = vec2<int>;
	using int3 = vec3<int>;
	using int4 = vec4<int>;

	// uint
	using uint2 = vec2<uint>;
	using uint3 = vec3<uint>;
	using uint4 = vec4<uint>;

	// byte
	using byte2 = vec2<byte>;
	using byte3 = vec3<byte>;
	using byte4 = vec4<byte>;

	template <class T, int Dim>
	constexpr bool any(const vec<T, Dim>& vec)
	{
		for (const auto& v : vec)
			if (v != 0)
				return true;
		return false;
	}

	template <class T, int Dim>
	constexpr bool all(const vec<T, Dim>& vec)
	{
		for (const auto& v : vec)
			if (v == 0)
				return false;
		return true;
	}

	// Cast

	template <class T, int Dim>
	constexpr auto& asfloat(vec<T, Dim>& in)
	{
		using RetType = vec<float, Dim>;
		static_assert(sizeof(RetType) == sizeof(vec<T, Dim>));
		return *((RetType*)&in);
	}


	// Math
#define VECTOR_FUNCTION_1(f, g)					    \
	template <class T, int Dim>						\
	constexpr vec<T, Dim> f(const vec<T, Dim>& in)	\
	{												\
		static_assert(2 <= Dim && Dim <= 4);		\
		vec<T, Dim> out;							\
		if constexpr (Dim > 0) out[0] = g(in[0]);	\
		if constexpr (Dim > 1) out[1] = g(in[1]);	\
		if constexpr (Dim > 2) out[2] = g(in[2]);	\
		if constexpr (Dim > 3) out[3] = g(in[3]);	\
		return out;									\
	}

#define VECTOR_FUNCTION_2(f, g)							                     \
	template <class T, int Dim>											     \
	constexpr vec<T, Dim> f(const vec<T, Dim>& in0, const vec<T, Dim>& in1)	 \
	{															             \
		static_assert(2 <= Dim && Dim <= 4);								 \
		vec<T, Dim> out;									                 \
		if constexpr (Dim > 0) out[0] = g(in0[0], in1[0]);				     \
		if constexpr (Dim > 1) out[1] = g(in0[1], in1[1]);				     \
		if constexpr (Dim > 2) out[2] = g(in0[2], in1[2]);				     \
		if constexpr (Dim > 3) out[3] = g(in0[3], in1[3]);				     \
		return out;												             \
	}

#define VECTOR_FUNCTION_3(f, g)																		 \
	template <class T, int Dim>																		 \
	constexpr vec<T, Dim> f(const vec<T, Dim>& in0, const vec<T, Dim>& in1, const vec<T, Dim>& in2)	 \
	{																								 \
		static_assert(2 <= Dim && Dim <= 4);														 \
		vec<T, Dim> out;																			 \
		if constexpr (Dim > 0) out[0] = g(in0[0], in1[0], in2[0]);									 \
		if constexpr (Dim > 1) out[1] = g(in0[1], in1[1], in2[1]);									 \
		if constexpr (Dim > 2) out[2] = g(in0[2], in1[2], in2[2]);									 \
		if constexpr (Dim > 3) out[3] = g(in0[3], in1[3], in2[3]);									 \
		return out;																					 \
	}

	VECTOR_FUNCTION_1(abs, std::abs)
	VECTOR_FUNCTION_1(acos, std::acos)
	VECTOR_FUNCTION_1(asin, std::asin)
	VECTOR_FUNCTION_1(atan, std::atan)
	VECTOR_FUNCTION_1(ceil, std::ceil)
	VECTOR_FUNCTION_1(floor, std::floor)
	VECTOR_FUNCTION_1(saturate, saturate)
	VECTOR_FUNCTION_1(radians, radians)
	VECTOR_FUNCTION_1(degrees, degrees)

	VECTOR_FUNCTION_2(min, std::min)
	VECTOR_FUNCTION_2(max, std::max)

	VECTOR_FUNCTION_3(clamp, clamp)

	template <class T, int Dim>
	constexpr auto dot(const vec<T, Dim>& a, const vec<T, Dim>& b)
	{
		static_assert(2 <= Dim && Dim <= 4);
		T result = 0.0f;
		if constexpr (Dim > 0) result += a[0] * b[0];
		if constexpr (Dim > 1) result += a[1] * b[1];
		if constexpr (Dim > 2) result += a[2] * b[2];
		if constexpr (Dim > 3) result += a[3] * b[3];
		return result;
	}

	template <class T>
	constexpr vec3<T> cross(const vec3<T>& a, const vec3<T>& b)
	{
		return vec3<T>(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
	}

	template <class T, int Dim>
	constexpr auto length_sqr(const vec<T, Dim>& v)
	{
		return dot(v, v);
	}

	template <class T, int Dim>
	constexpr auto length(const vec<T, Dim>& v)
	{
		return std::sqrt(length_sqr(v));
	}

	template <class T, int Dim>
	constexpr auto distance_sqr(const vec<T, Dim>& v0, const vec<T, Dim>& v1)
	{
		return length_sqr(v0 - v1);
	}

	template <class T, int Dim>
	constexpr auto distance(const vec<T, Dim>& v0, const vec<T, Dim>& v1)
	{
		return length(v0 - v1);
	}

	template <class T, int Dim>
	constexpr vec<T, Dim> normalize(const vec<T, Dim>& v)
	{
		auto rcpLen = T(1) / length(v);
		return v * rcpLen;
	}

	// ivec is not normalized, ivec is pointing to reflection point
	// nvec is normalized
	// r = i - 2*dot(i,n)*n
	template <class T, int Dim>
	constexpr vec<T, Dim> reflect(const vec<T, Dim>& ivec, const vec<T, Dim>& nvec)
	{
		return ivec - (T(2) * dot(ivec, nvec) * nvec);
	}

	template <class T, int Dim>
	constexpr vec<T, Dim> refract(const vec<T, Dim>& ivec, const vec<T, Dim>& nvec, T refractionIndex)
	{
		using scalar_t = typename T::scalar_type;

		scalar_t t = dot(ivec, nvec);
		scalar_t r = T(1) - refractionIndex * refractionIndex * (T(1) - t * t);

		if (r < 0) // Total internal reflection
		{
			return vec<T, Dim>(0);
		}
		else
		{
			T s = refractionIndex * t + sqrtf(r);
			return refractionIndex * ivec - s * nvec;
		}
	}

	template <class T, int Dim>
	constexpr bool refract(const T& unit_v, const T& unit_n, float ni_over_nt, T& refracted)
	{
		using scalar_t = typename T::scalar_type;

		scalar_t dt = dot(unit_v, unit_n);
		scalar_t discriminant = T(1) - (ni_over_nt * ni_over_nt * (T(1) - dt * dt));
		if (discriminant > 0)
		{
			refracted = ni_over_nt * (unit_v - unit_n * dt) - unit_n * std::sqrt(discriminant);
			return true;
		}
		else
		{
			// total internal reflection
			return false;
		}
	}

	//template <class T, int Dim>
	//constexpr vec<T, Dim> select(const vec<bool, Dim>& condition, const vec<T, Dim>& trueValue, const vec<T, Dim>& falseValue)
	//{
	//	vec<T, Dim> result;
	//	for (int i = 0; i < Dim; i++)
	//		result[i] = condition[i] ? trueValue[i] : falseValue[i];
	//	return result;
	//}
}
