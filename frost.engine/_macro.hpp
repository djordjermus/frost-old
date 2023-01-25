#pragma once
#if defined(FROST_ENGINE_DLL_BUILD)
	#define FROST_ENGINE _declspec(dllexport)
#else
	#define FROST_ENGINE _declspec(dllimport)
#endif