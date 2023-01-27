#include "frost.core/primitives.hpp"
#include "frost.core/pimpl.hpp"
#include "../_macro.hpp"
#pragma once
namespace frost::system
{
	class thread final : frost::pimpl<thread> 
	{
	public:

		inline thread(pimpl_t<thread> ptr) :
			frost::pimpl<thread>(ptr) {}
		template<class T>
		inline thread(void(*procedure)(T*), T* argument) :
			thread(create<T>(procedure, argument)) {}
		inline thread(thread&& move) noexcept :
			thread(move.detachPimpl()) {}
		inline thread& operator=(thread&& move) noexcept
		{
			swapPimpl(move);
			return *this;
		}
		inline ~thread()
		{
			join(this->getPimpl());
		}

		inline bool isRunning() const
		{
			return isRunning(getPimpl());
		}
		inline bool isJoinable() const
		{
			return isJoinable(getPimpl());
		}
		inline u64 getId() const
		{
			return getId(getPimpl());
		}
		inline void join() const
		{
			return join(getPimpl());
		}

		template<class T>
		static frost::pimpl_t<thread> create(void(*procedure)(T*), T* argument)
		{
			return create<void>
			(
				reinterpret_cast<void(*)(void*)>(procedure),
				reinterpret_cast<void*>(argument)
			);
		}

		static FROST_SYSTEM u64 getCallerId();
		template<>
		static FROST_SYSTEM frost::pimpl_t<thread> create<void>(void(*procedure)(void*), void* argument);
		static FROST_SYSTEM bool isRunning(frost::pimpl_t<thread> ptr);
		static FROST_SYSTEM bool isJoinable(frost::pimpl_t<thread> ptr);
		static FROST_SYSTEM u64 getId(frost::pimpl_t<thread> ptr);
		static FROST_SYSTEM void join(frost::pimpl_t<thread> ptr);
	};
}