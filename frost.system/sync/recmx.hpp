#include "../_macro.hpp"
#include "frost.core/pimpl.hpp"
#pragma once
namespace frost::system
{
	class recmx final : public pimpl<recmx>
	{
	public:

		inline recmx(pimpl_t<recmx> ptr) :
			pimpl<recmx>(ptr) {}
		inline recmx(bool auto_acquire) :
			recmx(create(auto_acquire)) {}
		inline recmx(pimpl<recmx>&& move) noexcept :
			recmx(move.detachPimpl()) {}
		inline recmx& operator=(pimpl<recmx>&& move) noexcept
		{
			swapPimpl(move);
			return *this;
		}
		inline ~recmx()
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
		inline u64 getSpin()
		{
			return getSpin(this->getPimpl());
		}



		static FROST_SYSTEM pimpl_t<recmx> create(bool auto_acquire);
		static FROST_SYSTEM void acquire(pimpl_t<recmx> ptr);
		static FROST_SYSTEM bool tryAcquire(pimpl_t<recmx> ptr);
		static FROST_SYSTEM void release(pimpl_t<recmx> ptr);
		static FROST_SYSTEM u64 getSpin(pimpl_t<recmx> ptr);
		static FROST_SYSTEM void destroy(pimpl_t<recmx> ptr);
	};
}