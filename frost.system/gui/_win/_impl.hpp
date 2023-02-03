#pragma once
#if defined(_WIN32) || defined(_WIN64)
#include <stdexcept>
#include <Windows.h>
#include <vector>
#include "../gui.hpp"
namespace frost
{
	template<>
	class impl_t<system::gui> final
	{
	public:
		HWND	hwnd			= nullptr;
		v2i32	win_rect		= v2i32();
		v2i32	cli_rect		= v2i32();
		v2i32	cursor_last		= v2i32(0, 0);
		f32		opacity			= 0.0f;
		rgba8	key				= rgba8();
		DWORD	thread_id		= 0;
		bool	cursor_inside	= false;

		std::vector<system::gui::resizeHandler*> _resize_handler;
		std::vector<system::gui::repositionHandler*> _reposition_handler;
		std::vector<system::gui::redrawHandler*> _redraw_handler;
		std::vector<system::gui::cursorEnterHandler*> _cursor_enter_handlers;
		std::vector<system::gui::cursorMoveHandler*> _cursor_move_handlers;
		std::vector<system::gui::cursorLeaveHandler*> _cursor_leave_handlers;
		std::vector<system::gui::closeHandler*> _close_handlers;
		std::vector<system::gui::destroyHandler*> _destroy_handlers;
	};

	ATOM getWindowClassAtom();
	int stateToInt(system::gui::state state);
	DWORD optionsToDword(system::gui::options options);
	system::gui::state stateFromInt(int state);
	system::gui::options optionsFromDword(DWORD options);
	void setOpacityAndTransparency(pimpl_t<system::gui> ptr, f32 opacity, const rgba8* color);
	
	pimpl_t<system::gui> GuiFromHwnd(HWND h);
	LRESULT guiProcedure(HWND h, UINT m, WPARAM w, LPARAM l);
	LRESULT wmMouseMove(HWND h, UINT m, WPARAM w, LPARAM l);
	LRESULT wmMouseLeave(HWND h, UINT m, WPARAM w, LPARAM l);
	LRESULT wmSize(HWND h, UINT m, WPARAM w, LPARAM l);
	LRESULT wmMove(HWND h, UINT m, WPARAM w, LPARAM l);
	LRESULT wmPaint(HWND h, UINT m, WPARAM w, LPARAM l);
	LRESULT wmCreate(HWND h, UINT m, WPARAM w, LPARAM l);
	LRESULT wmClose(HWND h, UINT m, WPARAM w, LPARAM l);
	LRESULT wmDestroy(HWND h, UINT m, WPARAM w, LPARAM l);
	frost::v2i32 vecFromLParam(LPARAM l);

#define ADD_HANDLER(V, H)\
	V.emplace_back(H)

#define REMOVE_HANDLER(V, H)\
	for(auto it = V.begin(), jt = V.end(); it != jt; it++)\
	{\
		if (*it == H) { V.erase(it); break; }\
	}

}
#endif