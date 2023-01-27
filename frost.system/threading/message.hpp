#include "frost.core/primitives.hpp"
#include "frost.core/pimpl.hpp"
#include "../_macro.hpp"
#pragma once
namespace frost::system
{
	class message final : public frost::pimpl<message>
	{
	public:
		inline message(frost::pimpl_t<message> ptr) :
			frost::pimpl<message>(ptr) {}
		inline message() :
			message(create()) {}
		inline message(const message& copy) :
			message(clone(copy.getPimpl())) {}
		inline message(const message&& copy) noexcept :
			message(clone(copy.getPimpl())) {}
		inline message(message&& move) noexcept :
			message(move.detachPimpl()) {}
		inline message& operator=(const message& copy)
		{
			destroy(this->getPimpl());
			(void)swapPimpl(clone(copy.getPimpl()));
			return *this;
		}
		inline message& operator=(const message&& copy) noexcept
		{
			destroy(this->getPimpl());
			(void)swapPimpl(clone(copy.getPimpl()));
			return *this;
		}
		inline message& operator=(message&& move) noexcept
		{
			swapPimpl(move);
			return *this;
		}

		inline void waitPull()
		{
			return waitPull(getPimpl());
		}
		inline void immediatePull()
		{
			return immediatePull(getPimpl());
		}
		inline void dispatch()
		{
			return dispatch(getPimpl());
		}

		static FROST_SYSTEM void initQueue();
		template<class T>
		static void send(u64 target_thread, void(*procedure)(T* argument), T* argument)
		{
			return send<void>
			(
				target_thread,
				reinterpret_cast<void(*)(void*)>(procedure),
				reinterpret_cast<void*>(argument)
			);
		}
		template<>
		static FROST_SYSTEM void send<void>(u64 target_thread, void(*procedure)(void* argument), void* argument);

		static FROST_SYSTEM pimpl_t<message> create();
		static FROST_SYSTEM pimpl_t<message> clone(pimpl_t<message> ptr);
		static FROST_SYSTEM void waitPull(pimpl_t<message> ptr);
		static FROST_SYSTEM void immediatePull(pimpl_t<message> ptr);
		static FROST_SYSTEM void dispatch(pimpl_t<message> ptr);
		static FROST_SYSTEM void destroy(pimpl_t<message> ptr);
	};
}