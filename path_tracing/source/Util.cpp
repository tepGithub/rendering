#include "util.h"

// RNG - Marsaglia's xor32
static uint32_t seed = 0x12345678;
uint32_t RandomUInt()
{
	seed ^= seed << 13;
	seed ^= seed >> 17;
	seed ^= seed << 5;
	return seed;
}
float RandomFloat() { return RandomUInt() * 2.3283064365387e-10f; }
float Rand( float range ) { return RandomFloat() * range; }
// local seed
uint32_t RandomUInt( uint32_t& seed )
{
	seed ^= seed << 13;
	seed ^= seed >> 17;
	seed ^= seed << 5;
	return seed;
}
float RandomFloat( uint32_t& seed ) { return RandomUInt( seed ) * 2.3283064365387e-10f; }