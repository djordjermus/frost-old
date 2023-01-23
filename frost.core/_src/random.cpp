#include "../random.hpp"
namespace frost
{
	random::random() :
		_seed(time(0)) {}

	// Generates a pseudo-random unsigned 64 bit integer in range [from, from + range)
	random::u64 random::rangeU(u64 from, u64 range) 
	{
		return from + (generate() % range);
	}

	// Generates a pseudo-random signed 64 bit integer in range [from, from + range)
	random::i64 random::rangeL(i64 from, i64 range) 
	{
		return from + (generate() % range);
	}

	// Generates a pseudo-random double in range [from, from + range)
	random::f64 random::rangeF(f64 from, f64 range) 
	{
		return from + fmod(generate() * 0.0000000000000001, range);
	}
}