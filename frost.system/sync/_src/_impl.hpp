#include "../mutex.hpp"
#include "../semaphore.hpp"
#include "../recmx.hpp"
#include <exception>
#pragma once

#if defined(_WIN32) || defined(_WIN64)
#include <Windows.h>
namespace frost
{
	template<>
	class impl_t<system::recmx>
	{
	public:
		HANDLE	mutex;
		u64		spin;
	};
}
#endif
