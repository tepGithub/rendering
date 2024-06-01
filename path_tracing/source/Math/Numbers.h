#pragma once

namespace Math
{
	template <class T> inline constexpr T e_v				= T(2.71828182845904523536);	// e
	template <class T> inline constexpr T log2e_v			= T(1.44269504088896340736);	// log2(e)
	template <class T> inline constexpr T log10e_v			= T(0.434294481903251827651);	// log10(e)
	template <class T> inline constexpr T ln2_v				= T(0.693147180559945309417);	// ln(2)
	template <class T> inline constexpr T ln10_v			= T(2.30258509299404568402);	// ln(10)
	template <class T> inline constexpr T pi_v				= T(3.14159265358979323846);	// pi
	template <class T> inline constexpr T pi_over_2_v		= T(1.57079632679489661923);	// pi/2
	template <class T> inline constexpr T pi_over_4_v		= T(0.785398163397448309616);	// pi/4
	template <class T> inline constexpr T one_over_pi_v		= T(0.318309886183790671538);	// 1/pi
	template <class T> inline constexpr T two_over_pi_v		= T(0.636619772367581343076);	// 2/pi
	template <class T> inline constexpr T two_over_sqrtpi_v	= T(1.12837916709551257390);	// 2/sqrt(pi)
	template <class T> inline constexpr T sqrt2_v			= T(1.41421356237309504880);	// sqrt(2)
	template <class T> inline constexpr T one_over_sqrt2_v	= T(0.707106781186547524401);	// 1/sqrt(2)

	constexpr float ef					= e_v<float>;
	constexpr float log2ef				= log2e_v<float>;
	constexpr float log10ef				= log10e_v<float>;
	constexpr float ln2f				= ln2_v<float>;
	constexpr float ln10f				= ln10_v<float>;
	constexpr float pif					= pi_v<float>;
	constexpr float pi_over_2f			= pi_over_2_v<float>;
	constexpr float pi_over_4f			= pi_over_4_v<float>;
	constexpr float one_over_pif		= one_over_pi_v<float>;
	constexpr float two_over_pif		= two_over_pi_v<float>;
	constexpr float two_over_sqrtpif	= two_over_sqrtpi_v<float>;
	constexpr float sqrt2f				= sqrt2_v<float>;
	constexpr float one_over_sqrt2f		= one_over_sqrt2_v<float>;

	constexpr double e					= e_v<double>;
	constexpr double log2e				= log2e_v<double>;
	constexpr double log10e				= log10e_v<double>;
	constexpr double ln2				= ln2_v<double>;
	constexpr double ln10				= ln10_v<double>;
	constexpr double pi					= pi_v<double>;
	constexpr double pi_over_2			= pi_over_2_v<double>;
	constexpr double pi_over_4			= pi_over_4_v<double>;
	constexpr double one_over_pi		= one_over_pi_v<double>;
	constexpr double two_over_pi		= two_over_pi_v<double>;
	constexpr double two_over_sqrtpi	= two_over_sqrtpi_v<double>;
	constexpr double sqrt2				= sqrt2_v<double>;
	constexpr double one_over_sqrt2		= one_over_sqrt2_v<double>;

	constexpr float epsf				= 1.19209290e-7f;
	constexpr float one_minus_epsf		= 0x1.fffffep-1;			// 0.999999940395355224609
	constexpr float one_plus_epsf		= 0x1.000002p+0;			// 1.00000011920928955078

	constexpr double eps				= 2.2204460492503131e-016;
	constexpr double one_minus_eps		= 0x1.fffffffffffffp-1;		// 0.999999999999999888978
	constexpr double one_plus_eps		= 0x1.0000000000001p+0;		// 1.00000000000000022204
}
