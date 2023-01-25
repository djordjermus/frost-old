#include "frost.core/vectors.hpp"
#include "../_macro.hpp"
#pragma once
namespace frost::system
{
	class cursor final
	{
	public:
		static FROST_SYSTEM frost::v2i32 getPosition();
		static FROST_SYSTEM void setPosition(const frost::v2i32& position);

	private:
		cursor() = delete;
		cursor(const cursor&) = delete;
		cursor(const cursor&&) = delete;
		cursor& operator=(const cursor&) = delete;
		cursor& operator=(const cursor&&) = delete;
		~cursor() = delete;
	};
}