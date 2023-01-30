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

	LRESULT guiProcedure(HWND h, UINT m, WPARAM w, LPARAM l) 
	{
		switch (m)
		{
		case WM_CREATE:
			return wmCreate(h, m, w, l);
		default:
			break;
		}
		return ::DefWindowProcW(h, m, w, l);
	}
	LRESULT wmCreate(HWND h, UINT m, WPARAM w, LPARAM l)
	{
		CREATESTRUCT* cs = reinterpret_cast<CREATESTRUCT*>(l);
		::SetWindowLongPtrW(h, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(cs->lpCreateParams));
		return ::DefWindowProcW(h, m, w, l);
	}
}
#endif