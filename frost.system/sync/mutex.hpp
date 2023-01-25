#include "../_macro.hpp"
#include "frost.core/pimpl.hpp"
#pragma once
namespace frost::system
{
	class mutex final : public pimpl<mutex>
	{
	public:
		
		inline mutex(pimpl_t<mutex> ptr) :
			pimpl<mutex>(ptr) {}
		inline mutex(bool auto_acquire) :
			mutex(create(auto_acquire)) {}
		inline mutex(pimpl<mutex>&& move) noexcept :
			mutex(move.detachPimpl()) {}
		inline mutex& operator=(pimpl<mutex>&& move) noexcept
		{
			swapPimpl(move);
			return *this;
		}
		inline ~mutex()
		{
			if (this->getPimpl())
				destroy(this->getPimpl());
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

		static FROST_SYSTEM pimpl_t<mutex> create(bool auto_acquire);
		static FROST_SYSTEM void acquire(pimpl_t<mutex> ptr);
		static FROST_SYSTEM bool tryAcquire(pimpl_t<mutex> ptr);
		static FROST_SYSTEM void release(pimpl_t<mutex> ptr);
		static FROST_SYSTEM void destroy(pimpl_t<mutex> ptr);
	};
}