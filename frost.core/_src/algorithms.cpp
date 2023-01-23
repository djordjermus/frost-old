#include "../algorithms.hpp"
namespace frost
{
	u64 algorithms::hashFNV1a(const u8* begin, const u8* end) 
	{
		u64 hash		= fnv1a_basis;
		const u8* read	= begin;
		while (read != end) 
		{
			hash = hash ^ *read;
			hash = hash * fnv1a_prime;
			read++;
		}
		return hash;
	}
	u64 algorithms::hashFNV1aContinue(u64 hash, const u8* begin, const u8* end)
	{
		const u8* read = begin;
		while (read != end)
		{
			hash = hash ^ *read;
			hash = hash * fnv1a_prime;
			read++;
		}
		return hash;
	}

}