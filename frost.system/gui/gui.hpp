#include "frost.core/primitives.hpp"
#include "frost.core/vectors.hpp"
#include "frost.core/pimpl.hpp"
#pragma once
namespace frost::system
{
	class gui final : public pimpl<gui>
	{
	public:


		static pimpl_t<gui> create();
		static void setWindowPosition(pimpl_t<gui> ptr, const v2i32& position);
		static void setWindowSize(pimpl_t<gui> ptr, const v2i32& size);
		static void destroy(pimpl_t<gui> ptr);
	};
}