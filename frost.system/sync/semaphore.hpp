#include "../_macro.hpp"
#include "frost.core/primitives.hpp"
#include "frost.core/pimpl.hpp"
#pragma once
namespace frost::system
{
	class semaphore final : public pimpl<semaphore>
	{
	public:

		inline semaphore(pimpl_t<semaphore> ptr) :
			pimpl<semaphore>(ptr) {}
		inline semaphore(i32 count, i32 max) :
			semaphore(create(count, max)) {}
		inline semaphore(pimpl<semaphore>&& move) noexcept :
			semaphore(move.detachPimpl()) {}
		inline semaphore& operator=(pimpl<semaphore>&& move) noexcept
		{
			swapPimpl(move);
			return *this;
		}
		inline ~semaphore()
		{
			if (getPimpl() != nullptr)
				destroy(getPimpl());
		}

		inline void acquire()
		{
			return acquire(this->getPimpl());
		}
		inline bool tryAcquire()
		{
			return tryAcquire(this->getPimpl());
		}
		inline void release()
		{
			return release(this->getPimpl());
		}

		static FROST_SYSTEM pimpl_t<semaphore> create(i32 count, i32 max);
		static FROST_SYSTEM void acquire(pimpl_t<semaphore> ptr);
		static FROST_SYSTEM bool tryAcquire(pimpl_t<semaphore> ptr);
		static FROST_SYSTEM void release(pimpl_t<semaphore> ptr);
		static FROST_SYSTEM void destroy(pimpl_t<semaphore> ptr);
	};
}