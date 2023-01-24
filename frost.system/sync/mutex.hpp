#include "frost.core/pimpl.hpp"
#pragma once
namespace frost::system
{
	class mutex final : public pimpl<mutex>
	{
	public:
		
		mutex(pimpl_t<mutex> ptr);
		mutex(bool auto_acquire);
		mutex(pimpl<mutex>&& move) noexcept;
		mutex& operator=(pimpl<mutex>&& move) noexcept;
		~mutex();

		void acquire();
		bool tryAcquire();
		void release();

		static pimpl_t<mutex> create(bool auto_acquire);
		static void acquire(pimpl_t<mutex> ptr);
		static bool tryAcquire(pimpl_t<mutex> ptr);
		static void release(pimpl_t<mutex> ptr);
		static void destroy(pimpl_t<mutex> ptr);
	};
}