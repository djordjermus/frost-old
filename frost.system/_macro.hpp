#pragma once
#if defined(FROST_SYSTEM_DLL_BUILD)
	#define FROST_SYSTEM _declspec(dllexport)
#else
	#define FROST_SYSTEM _declspec(dllimport)
#endif