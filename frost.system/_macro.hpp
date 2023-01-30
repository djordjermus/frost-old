#pragma once
#if defined(FROST_SYSTEM_DLL_BUILD)
	#define FROST_SYSTEM _declspec(dllexport)
#else
	#define FROST_SYSTEM _declspec(dllimport)
#endif

#define INLINE_BITWISE_ENUM(E)\
inline E operator|(E left, E right) { return E(unsigned long long(left) | unsigned long long(right)); }\
inline E operator&(E left, E right) { return E(unsigned long long(left) & unsigned long long(right)); }\
inline E operator^(E left, E right) { return E(unsigned long long(left) ^ unsigned long long(right)); }

