#include "frost.core/pimpl.hpp"
#pragma once
namespace frost::system
{
	class recmx final : public pimpl<recmx>
	{
	public:

		recmx(pimpl_t<recmx> ptr);
		recmx(bool auto_acquire);
		recmx(pimpl<recmx>&& move) noexcept;
		recmx& operator=(pimpl<recmx>&& move) noexcept;
		~recmx();



		void acquire();
		bool tryAcquire();
		void release();
		u64 getSpin();



		static pimpl_t<recmx> create(bool auto_acquire);
		static void acquire(pimpl_t<recmx> ptr);
		static bool tryAcquire(pimpl_t<recmx> ptr);
		static void release(pimpl_t<recmx> ptr);
		static u64 getSpin(pimpl_t<recmx> ptr);
		static void destroy(pimpl_t<recmx> ptr);
	};
}