#include "frost.core/primitives.hpp"
#include "frost.core/vectors.hpp"
#include "frost.core/string.hpp"
#include "frost.core/colors.hpp"
#include "../_macro.hpp"
#include "eventData.hpp"
#pragma once
namespace frost::system
{
	class gui final : public frost::pimpl<gui>
	{
	public:
		enum class state : u32;
		enum class options : u32;
		class description;

		inline gui(frost::pimpl_t<gui> ptr) :
			frost::pimpl<gui>(ptr) {}
		inline gui(const description& desc) :
			frost::pimpl<gui>(create(desc)) {}
		inline ~gui()
		{
			if (getPimpl() != nullptr)
				destroy(getPimpl());
		}

		inline bool isAlive() const
		{
			return isAlive(getPimpl());
		}


		using repositionHandler		= frost::eventHandler<frost::pimpl_t<gui>, repositionGuiEvent>;
		using resizeHandler			= frost::eventHandler<frost::pimpl_t<gui>, resizeGuiEvent>;
		using redrawHandler			= frost::eventHandler<frost::pimpl_t<gui>, redrawGuiEvent>;
		using cursorEnterHandler	= frost::eventHandler<frost::pimpl_t<gui>, cursorEnterGuiEvent>;
		using cursorMoveHandler		= frost::eventHandler<frost::pimpl_t<gui>, cursorMoveGuiEvent>;
		using cursorLeaveHandler	= frost::eventHandler<frost::pimpl_t<gui>, cursorLeaveGuiEvent>;
		using closeHandler			= frost::eventHandler<frost::pimpl_t<gui>, closeGuiEvent>;
		using destroyHandler		= frost::eventHandler<frost::pimpl_t<gui>, destroyGuiEvent>;

#define AUTO_HANDLER_INTERFACE(T)\
inline void addHandler(frost::eventHandler<frost::pimpl_t<gui>, T>& handler) { addHandler(getPimpl(), handler); }\
inline void removeHandler(frost::eventHandler<frost::pimpl_t<gui>, T>& handler) { removeHandler(getPimpl(), handler); }
		AUTO_HANDLER_INTERFACE(repositionGuiEvent);
		AUTO_HANDLER_INTERFACE(resizeGuiEvent);
		AUTO_HANDLER_INTERFACE(redrawGuiEvent);
		AUTO_HANDLER_INTERFACE(cursorEnterGuiEvent);
		AUTO_HANDLER_INTERFACE(cursorMoveGuiEvent);
		AUTO_HANDLER_INTERFACE(cursorLeaveGuiEvent);
		// BUTTON DOWN/UP/DOUBLE CLICK
		// KEY DOWN/UP
		AUTO_HANDLER_INTERFACE(closeGuiEvent);
		AUTO_HANDLER_INTERFACE(destroyGuiEvent);
#undef AUTO_HANDLER_INTERFACE

		static FROST_SYSTEM pimpl_t<gui> create(const description& desc);
		static FROST_SYSTEM void setWindowPosition(pimpl_t<gui> ptr, const v2i32& position);
		static FROST_SYSTEM void setWindowSize(pimpl_t<gui> ptr, const v2i32& size);
		static FROST_SYSTEM void setCaption(pimpl_t<gui> ptr, pimpl_t<string> caption);
		static FROST_SYSTEM void setState(pimpl_t<gui> ptr, state state);
		static FROST_SYSTEM void setOptions(pimpl_t<gui> ptr, options options);
		static FROST_SYSTEM void setOpacity(pimpl_t<gui> ptr, f32 opacity);
		static FROST_SYSTEM void setTransparencyKey(pimpl_t<gui> ptr, frost::rgba8 color);
		static FROST_SYSTEM void setTransparencyEnabled(pimpl_t<gui> ptr, frost::rgba8 color);

		static FROST_SYSTEM bool isAlive(pimpl_t<gui> ptr);
		static FROST_SYSTEM v2i32 getWindowPosition(pimpl_t<gui> ptr);
		static FROST_SYSTEM v2i32 getWindowSize(pimpl_t<gui> ptr);
		static FROST_SYSTEM pimpl_t<string> getCaption(pimpl_t<gui> ptr);
		static FROST_SYSTEM state getState(pimpl_t<gui> ptr);
		static FROST_SYSTEM options getOptions(pimpl_t<gui> ptr);
		static FROST_SYSTEM f32 getOpacity(pimpl_t<gui> ptr);
		static FROST_SYSTEM rgba8 getTransparencyKey(pimpl_t<gui> ptr);
		static FROST_SYSTEM bool isTransparencyEnabled(pimpl_t<gui> ptr);
		static FROST_SYSTEM void destroy(pimpl_t<gui> ptr);

		static FROST_SYSTEM void addHandler(pimpl_t<gui> ptr, repositionHandler& handler);
		static FROST_SYSTEM void addHandler(pimpl_t<gui> ptr, resizeHandler& handler);
		static FROST_SYSTEM void addHandler(pimpl_t<gui> ptr, redrawHandler& handler);
		static FROST_SYSTEM void addHandler(pimpl_t<gui> ptr, cursorEnterHandler& handler);
		static FROST_SYSTEM void addHandler(pimpl_t<gui> ptr, cursorMoveHandler& handler);
		static FROST_SYSTEM void addHandler(pimpl_t<gui> ptr, cursorLeaveHandler& handler);
		static FROST_SYSTEM void addHandler(pimpl_t<gui> ptr, closeHandler& handler);
		static FROST_SYSTEM void addHandler(pimpl_t<gui> ptr, destroyHandler& handler);

		static FROST_SYSTEM void removeHandler(pimpl_t<gui> ptr, repositionHandler& handler);
		static FROST_SYSTEM void removeHandler(pimpl_t<gui> ptr, resizeHandler& handler);
		static FROST_SYSTEM void removeHandler(pimpl_t<gui> ptr, redrawHandler& handler);
		static FROST_SYSTEM void removeHandler(pimpl_t<gui> ptr, cursorEnterHandler& handler);
		static FROST_SYSTEM void removeHandler(pimpl_t<gui> ptr, cursorMoveHandler& handler);
		static FROST_SYSTEM void removeHandler(pimpl_t<gui> ptr, cursorLeaveHandler& handler);
		static FROST_SYSTEM void removeHandler(pimpl_t<gui> ptr, closeHandler& handler);
		static FROST_SYSTEM void removeHandler(pimpl_t<gui> ptr, destroyHandler& handler);

		enum class state : u32
		{
			hidden		= 0x00,
			normal		= 0x01,
			minimized	= 0x02,
			maximized	= 0x03
		};

		enum class options : u32
		{
			none			= 0ul,
			resizable		= (1ul << 0ul),
			captioned		= (1ul << 1ul),
			minimize_button	= (1ul << 2ul),
			maximize_button	= (1ul << 3ul),
			all				= 0b1111
		};

		class description
		{
		public:
			v2i32	position	= v2i32(200, 200);
			v2i32	size		= v2i32(1280, 720);
			string	caption		= L"Frost a0.0.1";
			state	state		= state::normal;
			options	options		= options::all;
		};
	};
	INLINE_BITWISE_ENUM(gui::options);
}