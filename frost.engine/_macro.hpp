#pragma once
#if defined(FROST_DLL_BUILD)
	#define FROST_API _declspec(dllexport)
#else
	#define FROST_API _declspec(dllimport)
#endif