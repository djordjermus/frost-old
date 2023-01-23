#include "primitives.hpp"
#pragma once
namespace frost
{
	class algorithms 
	{
	public:
		static u64 hashFNV1a(const u8* begin, const u8* end);
		static u64 hashFNV1aContinue(u64 hash, const u8* begin, const u8* end);

		static constexpr u64 fnv1a_basis = 14695981039346656037;
		static constexpr u64 fnv1a_prime = 1099511628211;
	};
}