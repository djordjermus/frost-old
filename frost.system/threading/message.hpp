#include "frost.core/pimpl.hpp"
#include "../_macro.hpp"
#pragma once
namespace frost::system
{
	class message final : public frost::pimpl<message>
	{
	public:


		static FROST_SYSTEM void initQueue();
		static FROST_SYSTEM pimpl_t<message> create();
		static FROST_SYSTEM pimpl_t<message> clone(pimpl_t<message> ptr);
		static FROST_SYSTEM void waitPull(pimpl_t<message> ptr);
		static FROST_SYSTEM void immediatePull(pimpl_t<message> ptr);
		static FROST_SYSTEM void destroy(pimpl_t<message> ptr);
	};
}