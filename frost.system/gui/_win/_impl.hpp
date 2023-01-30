#pragma once
#if defined(_WIN32) || defined(_WIN64)
#include <stdexcept>
#include <Windows.h>
#include "../gui.hpp"
namespace frost
{
	template<>
	class impl_t<system::gui> final
	{
	public:
		HWND	hwnd		= nullptr;
		v2i32	win_rect	= v2i32();
		v2i32	cli_rect	= v2i32();
		f32		opacity		= 0.0f;
		rgba8	key			= rgba8();

	};

	ATOM getWindowClassAtom();
	int stateToInt(system::gui::state state);
	DWORD optionsToDword(system::gui::options options);
	system::gui::state stateFromInt(int state);
	system::gui::options optionsFromDword(DWORD options);
	void setOpacityAndTransparency(pimpl_t<system::gui> ptr, f32 opacity, const rgba8* color);
	
	LRESULT guiProcedure(HWND h, UINT m, WPARAM w, LPARAM l);
	LRESULT wmCreate(HWND h, UINT m, WPARAM w, LPARAM l);

}
#endif