#if defined(_WIN32) || defined(_WIN64)
#include <Windows.h>
#include "../cursor.hpp"

namespace frost::system 
{
	frost::v2i32 cursor::getPosition() 
	{
		POINT pt{};
		::GetCursorPos(&pt);
		return frost::v2i32(pt.x, pt.y);
	}
	void cursor::setPosition(const frost::v2i32& position)
	{
		::SetCursorPos(position.x, position.y);
	}
}

#endif