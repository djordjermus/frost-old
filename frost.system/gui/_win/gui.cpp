#if defined(_WIN32) || defined(_WIN64)
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

#define AUTO_DEFINE_HANDLER(V, E)\
	void gui::addHandler(pimpl_t<gui> ptr, frost::eventHandler<frost::pimpl_t<gui>, E>& handler)\
	{ V.emplace_back(&handler); }\
	void gui::removeHandler(pimpl_t<gui> ptr, frost::eventHandler<frost::pimpl_t<gui>, E>& handler)\
	{\
		for (auto it = V.begin(), jt = V.end(); it != jt; it++) {\
			if (*it == &handler) { V.erase(it); break; }\
		}\
	}
#define AUTO_SIGNAL_HANDLER(V, S, E)\
	for (auto it = V.begin(), jt = V.end(); it != jt; it++) (*it)->handle(S, E);

	AUTO_DEFINE_HANDLER(ptr->_reposition_handler,		repositionGuiEvent);
	AUTO_DEFINE_HANDLER(ptr->_resize_handler,			resizeGuiEvent);
	AUTO_DEFINE_HANDLER(ptr->_redraw_handler,			redrawGuiEvent);
	AUTO_DEFINE_HANDLER(ptr->_cursor_enter_handlers,	cursorEnterGuiEvent);
	AUTO_DEFINE_HANDLER(ptr->_cursor_move_handlers,		cursorMoveGuiEvent);
	AUTO_DEFINE_HANDLER(ptr->_cursor_leave_handlers,	cursorLeaveGuiEvent);
	AUTO_DEFINE_HANDLER(ptr->_close_handlers,			closeGuiEvent);
	AUTO_DEFINE_HANDLER(ptr->_destroy_handlers,			destroyGuiEvent);
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
