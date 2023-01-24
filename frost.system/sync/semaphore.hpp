#include "frost.core/primitives.hpp"
#include "frost.core/pimpl.hpp"
#pragma once
namespace frost::system
{
	class semaphore final : public pimpl<semaphore>
	{
	public:

		semaphore(pimpl_t<semaphore> ptr);
		semaphore(i32 count, i32 max);
		semaphore(pimpl<semaphore>&& move) noexcept;
		semaphore& operator=(pimpl<semaphore>&& move) noexcept;
		~semaphore();

		void acquire();
		bool tryAcquire();
		void release();

		static pimpl_t<semaphore> create(i32 count, i32 max);
		static void acquire(pimpl_t<semaphore> ptr);
		static bool tryAcquire(pimpl_t<semaphore> ptr);
		static void release(pimpl_t<semaphore> ptr);
		static void destroy(pimpl_t<semaphore> ptr);
	};
}