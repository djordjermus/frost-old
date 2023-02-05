#if defined(_WIN32) || defined(_WIN64)
#include <iostream>
#include "_impl.hpp"
namespace frost::system
{
	pimpl_t<gui> gui::create(const description& desc)
	{
		ATOM	atom		= frost::getWindowClassAtom();
		DWORD	style		= frost::optionsToDword(desc.options);
		DWORD	exstyle		= WS_EX_LAYERED;
		int		show_cmd	= frost::stateToInt(desc.state);
		
		if (atom == 0)
			throw std::exception("Failed to create window - could not create window atom.");

		pimpl_t<gui> ret = new impl_t<gui>();
		ret->hwnd = ::CreateWindowExW
		(
			exstyle, (LPCWSTR)atom, desc.caption.begin(), style,
			desc.position.x, desc.position.y, desc.size.x, desc.size.y,
			nullptr, nullptr, nullptr, reinterpret_cast<LPVOID>(ret)
		);
		ret->thread_id = ::GetCurrentThreadId();
		frost::setOpacityAndTransparency(ret, 1.0f, nullptr);

		RAWINPUTDEVICE rid[3] = {};
		for (RAWINPUTDEVICE& device : rid)
		{
			device.hwndTarget	= ret->hwnd;
			device.dwFlags		= RIDEV_DEVNOTIFY;
			device.usUsagePage	= 0x01;
		}
		rid[0].usUsage		= 0x01;
		rid[1].usUsage		= 0x02;
		rid[2].usUsage		= 0x06;

		if (::RegisterRawInputDevices(rid, sizeof(rid) / sizeof(*rid), sizeof(*rid)) == FALSE)
		{
			::DestroyWindow(ret->hwnd);
			delete ret;
			throw std::exception("Failed to capture input for created window");
		}

		::ShowWindow(ret->hwnd, show_cmd);

		return ret;
	}
	void gui::setWindowPosition(pimpl_t<gui> ptr, const v2i32& position){}
	void gui::setWindowSize(pimpl_t<gui> ptr, const v2i32& size){}
	void gui::setCaption(pimpl_t<gui> ptr, pimpl_t<string> caption){}
	void gui::setState(pimpl_t<gui> ptr, gui::state state){}
	void gui::setOptions(pimpl_t<gui> ptr, gui::options options){}
	void gui::setOpacity(pimpl_t<gui> ptr, f32 opacity){}
	void gui::setTransparencyKey(pimpl_t<gui> ptr, frost::rgba8 color){}
	void gui::setTransparencyEnabled(pimpl_t<gui> ptr, frost::rgba8 color){}

	bool gui::isAlive(pimpl_t<gui> ptr)
	{
		return static_cast<bool>(::IsWindow(ptr->hwnd));
	}
	v2i32 gui::getWindowPosition(pimpl_t<gui> ptr){ return {}; }
	v2i32 gui::getWindowSize(pimpl_t<gui> ptr){ return {}; }
	pimpl_t<string> gui::getCaption(pimpl_t<gui> ptr){ return {}; }
	gui::state gui::getState(pimpl_t<gui> ptr){ return {}; }
	gui::options gui::getOptions(pimpl_t<gui> ptr){ return {}; }
	f32 gui::getOpacity(pimpl_t<gui> ptr){ return {}; }
	rgba8 gui::getTransparencyKey(pimpl_t<gui> ptr){ return {}; }
	bool gui::isTransparencyEnabled(pimpl_t<gui> ptr){ return {}; }
	void gui::destroy(pimpl_t<gui> ptr)
	{
		if (ptr == nullptr)
			throw std::invalid_argument("Failed to destroy gui - gui is null.");

		if (::IsWindow(ptr->hwnd) != FALSE)
			::DestroyWindow(ptr->hwnd);

		delete ptr;
	}

#define AUTO_DEFINE_HANDLER(V, H)\
	void gui::addHandler(pimpl_t<gui> ptr, H& handler)\
	{ V.emplace_back(&handler); }\
	void gui::removeHandler(pimpl_t<gui> ptr, H& handler)\
	{\
		for (auto it = V.begin(), jt = V.end(); it != jt; it++) {\
			if (*it == &handler) { V.erase(it); break; }\
		}\
	}
	AUTO_DEFINE_HANDLER(ptr->_reposition_handler,		gui::repositionHandler);
	AUTO_DEFINE_HANDLER(ptr->_resize_handler,			gui::resizeHandler);
	AUTO_DEFINE_HANDLER(ptr->_redraw_handler,			gui::redrawHandler);
	AUTO_DEFINE_HANDLER(ptr->_cursor_enter_handlers,	gui::cursorEnterHandler);
	AUTO_DEFINE_HANDLER(ptr->_cursor_move_handlers,		gui::cursorMoveHandler);
	AUTO_DEFINE_HANDLER(ptr->_cursor_leave_handlers,	gui::cursorLeaveHandler);
	AUTO_DEFINE_HANDLER(ptr->_mouse_move_handlers,		gui::mouseMoveHandler);
	AUTO_DEFINE_HANDLER(ptr->_scroll_wheel_handlers,	gui::scrollWheelHandler);
	AUTO_DEFINE_HANDLER(ptr->_key_down_handlers,		gui::keyDownHandler);
	AUTO_DEFINE_HANDLER(ptr->_key_up_handlers,			gui::keyUpHandler);
	AUTO_DEFINE_HANDLER(ptr->_close_handlers,			gui::closeHandler);
	AUTO_DEFINE_HANDLER(ptr->_destroy_handlers,			gui::destroyHandler);
#undef AUTO_DEFINE_HANDLER

}


namespace frost
{
	ATOM getWindowClassAtom()
	{
		static ATOM ret = 0;
		if (ret == 0)
		{
			WNDCLASSEXW wc{};
			wc.cbSize			= sizeof(wc);
			wc.cbWndExtra		= sizeof(pimpl_t<system::gui>);
			wc.style			= CS_OWNDC | CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS;
			wc.lpfnWndProc		= guiProcedure;
			wc.hCursor			= ::LoadCursorW(nullptr, IDC_ARROW);
			// wc.hbrBackground	= ::CreateSolidBrush(RGB(255, 255, 255));
			wc.lpszClassName	= L"FROST_WINDOW_CLASS_000001";

			ret = ::RegisterClassExW(&wc);
		}
		return ret;
	}
	int stateToInt(system::gui::state state)
	{
		switch (state)
		{
		case system::gui::state::hidden:	return SW_HIDE;
		case system::gui::state::normal:	return SW_SHOWNORMAL;
		case system::gui::state::minimized:	return SW_SHOWMINIMIZED;
		case system::gui::state::maximized:	return SW_SHOWMAXIMIZED;
		default:
			throw std::invalid_argument("Invalid system::gui::state.");
		}
	}
	DWORD optionsToDword(system::gui::options options)
	{
		DWORD ret = 0;
		if ((options & system::gui::options::resizable) == system::gui::options::resizable)
			ret = ret | WS_SIZEBOX;
		if ((options & system::gui::options::captioned) == system::gui::options::captioned)
			ret = ret | WS_CAPTION;
		if ((options & system::gui::options::minimize_button) == system::gui::options::minimize_button)
			ret = ret | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
		if ((options & system::gui::options::maximize_button) == system::gui::options::maximize_button)
			ret = ret | WS_CAPTION | WS_SYSMENU | WS_MAXIMIZEBOX;

		if ((ret & WS_CAPTION) != WS_CAPTION)
			ret = ret | WS_POPUP;

		return ret;
	}
	system::gui::state stateFromInt(int state)
	{
		switch (state)
		{
		case SW_HIDE:			return system::gui::state::hidden;
		case SW_SHOWNORMAL:		return system::gui::state::normal;
		case SW_SHOWMINIMIZED:	return system::gui::state::minimized;
		case SW_SHOWMAXIMIZED:	return system::gui::state::maximized;
		default:
			throw std::invalid_argument("Invalid system::gui::state.");
		}
	}
	system::gui::options optionsFromDword(DWORD options)
	{
		system::gui::options ret = system::gui::options::none;
		if ((options & WS_SIZEBOX) == WS_SIZEBOX)
			ret = ret | system::gui::options::resizable;
		if ((options & WS_CAPTION) == WS_CAPTION)
			ret = ret | system::gui::options::captioned;
		if ((options & WS_MINIMIZEBOX) == WS_MINIMIZEBOX)
			ret = ret | system::gui::options::minimize_button;
		if ((options & WS_MAXIMIZEBOX) == WS_MAXIMIZEBOX)
			ret = ret | system::gui::options::maximize_button;
		return ret;
	}
	void setOpacityAndTransparency(pimpl_t<system::gui> ptr, f32 opacity, const rgba8* color)
	{
		bool use_opacity = opacity < 1.0f;
		bool use_key = color != nullptr;

		ptr->opacity	= use_opacity ? (opacity < 0.0f ? 0.0f : opacity) : 1.0f;
		ptr->key		= use_key ? *color : ptr->key;

		COLORREF col = !use_key ? 0 : RGB(color->r, color->g, color->b);
		::SetLayeredWindowAttributes
		(
			ptr->hwnd,
			col,
			static_cast<BYTE>(opacity * 255),
			(opacity == 1.0f ? 0 : LWA_ALPHA) | (color == nullptr ? 0 : LWA_COLORKEY)
		);
		ptr->opacity = opacity;
		ptr->key = color == nullptr ? rgba8() : *color;
	}

	pimpl_t<system::gui> GuiFromHwnd(HWND h)
	{
		LONG_PTR ret = ::GetWindowLongPtrW(h, GWLP_USERDATA);
		return reinterpret_cast<pimpl_t<system::gui>>(ret);
	}
	LRESULT guiProcedure(HWND h, UINT m, WPARAM w, LPARAM l)
	{
		switch (m)
		{
		case WM_DEVICECHANGE:
			break;
		case WM_INPUT:
			return wmInput(h, m, w, l);
		case WM_MOUSEMOVE:
			return wmMouseMove(h, m, w, l);
		case WM_MOUSELEAVE:
			return wmMouseLeave(h, m, w, l);
		case WM_MOVE:
			return wmMove(h, m, w, l);
		case WM_SIZE:
			return wmSize(h, m, w, l);
		case WM_PAINT:
			return wmPaint(h, m, w, l);
		case WM_CREATE:
			return wmCreate(h, m, w, l);
		case WM_CLOSE:
			return wmClose(h, m, w, l);
		case WM_DESTROY:
			return wmDestroy(h, m, w, l);
		default:
			return ::DefWindowProcW(h, m, w, l);
		}
		return ::DefWindowProcW(h, m, w, l);
	}

#define AUTO_SIGNAL_HANDLER(V, S, E)\
for (auto it = V.begin(), jt = V.end(); it != jt; it++) (*it)->handle(S, E);
	LRESULT wmInput(HWND h, UINT m, WPARAM w, LPARAM l)
	{
		auto gui = GuiFromHwnd(h);
		if (gui == nullptr)
			return ::DefWindowProcW(h, m, w, l);
		
		RAWINPUT ri = {};
		UINT sz = sizeof(ri);
		bool success = ::GetRawInputData((HRAWINPUT)l, RID_INPUT, &ri, &sz, sizeof(ri.header)) != -1;
		if (!success)
			return ::DefWindowProcW(h, m, w, l);

		if (ri.header.dwType == RIM_TYPEMOUSE)
		{
			auto& data = ri.data.mouse;
			if (data.lLastX != 0 || data.lLastY != 0)
			{
				frost::system::mouseMoveGuiEvent e(data.lLastX, data.lLastY);
				AUTO_SIGNAL_HANDLER(gui->_mouse_move_handlers, gui, e);
				if (e.doDefaultAction())
					return ::DefWindowProcW(h, m, w, l);
				else
					return 0;
			}
			if ((data.usButtonFlags & RI_MOUSE_WHEEL) == RI_MOUSE_WHEEL)
			{
				frost::system::scrollWheelGuiEvent e(0, (i16)(u16)data.usButtonData / 120);
				AUTO_SIGNAL_HANDLER(gui->_scroll_wheel_handlers, gui, e);
				if (e.doDefaultAction())
					return ::DefWindowProcW(h, m, w, l);
				else
					return 0;
			}
			if ((data.usButtonFlags & RI_MOUSE_WHEEL) == RI_MOUSE_WHEEL)
			{
				frost::system::scrollWheelGuiEvent e((i16)(u16)data.usButtonData / 120, 0);																									
				AUTO_SIGNAL_HANDLER(gui->_scroll_wheel_handlers, gui, e);
				if (e.doDefaultAction())
					return ::DefWindowProcW(h, m, w, l);
				else
					return 0;
			}

		}

		if (ri.header.dwType == RIM_TYPEKEYBOARD)
		{
			auto& data = ri.data.keyboard;
			if (data.Flags == RI_KEY_MAKE)
			{	// Key down TODO USE MAKE CODE
				frost::system::keyDownGuiEvent e((frost::pimpl_t<frost::system::key>)data.VKey);
				AUTO_SIGNAL_HANDLER(gui->_key_down_handlers, gui, e);
				if (e.doDefaultAction())
					return ::DefWindowProcW(h, m, w, l);
				else
					return 0;
			}
			else if ((data.Flags & RI_KEY_BREAK) == RI_KEY_BREAK)
			{	// Key up TODO USE MAKE CODE
				frost::system::keyUpGuiEvent e((frost::pimpl_t<frost::system::key>)data.VKey);
				AUTO_SIGNAL_HANDLER(gui->_key_up_handlers, gui, e);
				if (e.doDefaultAction())
					return ::DefWindowProcW(h, m, w, l);
				else
					return 0;
			}
			else if ((data.Flags & RI_KEY_E0) == RI_KEY_E0)
			{	// Key up TODO USE MAKE CODE
				frost::system::keyDownGuiEvent e((frost::pimpl_t<frost::system::key>)data.VKey);
				AUTO_SIGNAL_HANDLER(gui->_key_down_handlers, gui, e);
				if (e.doDefaultAction())
					return ::DefWindowProcW(h, m, w, l);
				else
					return 0;
			}
			else if ((data.Flags & RI_KEY_E1) == RI_KEY_E1)
			{	// Key up TODO USE MAKE CODE
				frost::system::keyUpGuiEvent e((frost::pimpl_t<frost::system::key>)data.VKey);
				AUTO_SIGNAL_HANDLER(gui->_key_up_handlers, gui, e);
				if (e.doDefaultAction())
					return ::DefWindowProcW(h, m, w, l);
				else
					return 0;
			}
		}
		return ::DefWindowProcW(h, m, w, l);
	}

	LRESULT wmMouseMove(HWND h, UINT m, WPARAM w, LPARAM l)
	{
		auto gui = GuiFromHwnd(h);
		if (gui == nullptr)
			return ::DefWindowProcW(h, m, w, l);

		gui->cursor_last = vecFromLParam(l);
		if (!gui->cursor_inside)
		{
			gui->cursor_inside = true;

			// Track mouse leave
			TRACKMOUSEEVENT tme;
			tme.cbSize		= sizeof(tme);
			tme.dwFlags		= TME_LEAVE;
			tme.hwndTrack	= h;
			::TrackMouseEvent(&tme);

			frost::system::cursorEnterGuiEvent e(gui->cursor_last);
			AUTO_SIGNAL_HANDLER(gui->_cursor_enter_handlers, gui, e);
			if (e.doDefaultAction())
				return ::DefWindowProcW(h, m, w, l);
			else
				return 0;
		}
		else
		{
			frost::system::cursorMoveGuiEvent e(gui->cursor_last);
			AUTO_SIGNAL_HANDLER(gui->_cursor_move_handlers, gui, e);
			if (e.doDefaultAction())
				return ::DefWindowProcW(h, m, w, l);
			else
				return 0;
		}
	}

	LRESULT wmMouseLeave(HWND h, UINT m, WPARAM w, LPARAM l)
	{
		auto gui = GuiFromHwnd(h);
		if (gui == nullptr)
			return ::DefWindowProcW(h, m, w, l);

		gui->cursor_inside = false;

		frost::system::cursorLeaveGuiEvent e(gui->cursor_last);
		AUTO_SIGNAL_HANDLER(gui->_cursor_leave_handlers, gui, e);
		if (e.doDefaultAction())
			return ::DefWindowProcW(h, m, w, l);
		else
			return 0;
	}

	LRESULT wmMove(HWND h, UINT m, WPARAM w, LPARAM l)
	{
		auto gui = GuiFromHwnd(h);
		if (gui == nullptr)
			return ::DefWindowProcW(h, m, w, l);

		frost::system::repositionGuiEvent e(vecFromLParam(l));
		AUTO_SIGNAL_HANDLER(gui->_reposition_handler, gui, e);
		if (e.doDefaultAction())
			return ::DefWindowProcW(h, m, w, l);
		else
			return 0;
	}

	LRESULT wmSize(HWND h, UINT m, WPARAM w, LPARAM l)
	{
		auto gui = GuiFromHwnd(h);
		if (gui == nullptr)
			return ::DefWindowProcW(h, m, w, l);

		frost::system::resizeGuiEvent e(vecFromLParam(l));
		AUTO_SIGNAL_HANDLER(gui->_resize_handler, gui, e);
		if (e.doDefaultAction())
			return ::DefWindowProcW(h, m, w, l);
		else
			return 0;
	}

	LRESULT wmPaint(HWND h, UINT m, WPARAM w, LPARAM l)
	{
		auto gui = GuiFromHwnd(h);
		if (gui == nullptr)
			return ::DefWindowProcW(h, m, w, l);

		PAINTSTRUCT psPaint;
		HDC hdc = BeginPaint(h, &psPaint);
		EndPaint(h, &psPaint);

		system::redrawGuiEvent e;
		AUTO_SIGNAL_HANDLER(gui->_redraw_handler, gui, e);
		if (e.doDefaultAction())
			return ::DefWindowProcW(h, m, w, l);
		else
			return 0;
	}

	LRESULT wmCreate(HWND h, UINT m, WPARAM w, LPARAM l)
	{
		CREATESTRUCT* cs = reinterpret_cast<CREATESTRUCT*>(l);
		::SetWindowLongPtrW(h, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(cs->lpCreateParams));
		return ::DefWindowProcW(h, m, w, l);
	}

	LRESULT wmClose(HWND h, UINT m, WPARAM w, LPARAM l)
	{
		auto gui = GuiFromHwnd(h);
		if (gui == nullptr)
			return ::DefWindowProcW(h, m, w, l);

		system::closeGuiEvent e;
		AUTO_SIGNAL_HANDLER(gui->_close_handlers, gui, e);
		if (e.doDefaultAction())
			return ::DefWindowProcW(h, m, w, l);
		else
			return 0;
	}

	LRESULT wmDestroy(HWND h, UINT m, WPARAM w, LPARAM l)
	{
		auto gui = GuiFromHwnd(h);
		if (gui == nullptr)
			return ::DefWindowProcW(h, m, w, l);
		
		system::destroyGuiEvent e;
		AUTO_SIGNAL_HANDLER(gui->_destroy_handlers, gui, e);

		if (e.doDefaultAction())
		{
			gui->hwnd = nullptr;
			
			return ::DefWindowProcW(h, m, w, l);
		}
		else
		{
			return 0;
		}
	}

	frost::v2i32 vecFromLParam(LPARAM l)
	{
		return frost::v2i32((i32)(u16)(l & 0xFFFF), (i32)(u16)((l >> 16) & 0xFFFF));
	}
}
#endif
