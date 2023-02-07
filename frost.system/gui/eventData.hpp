#include "frost.core/vectors.hpp"
#include "frost.core/eventData.h"
#include "frost.core/pimpl.hpp"
#include "../input/key.hpp"
#include "../_macro.hpp"
namespace frost::system
{
	class guiEvent : public frost::eventData
	{
	public:
		guiEvent() = default;

		bool FROST_SYSTEM doDefaultAction() const;
		void FROST_SYSTEM preventDefault();

	private:
		bool _prevent_default = false;
	};

	class repositionGuiEvent : public guiEvent
	{
	public:
		FROST_SYSTEM repositionGuiEvent(const frost::v2i32& position);
		frost::v2i32 FROST_SYSTEM getPosition() const;

	private:
		frost::v2i32 _position;
	};

	class resizeGuiEvent : public guiEvent
	{
	public:
		FROST_SYSTEM resizeGuiEvent(const frost::v2i32& position);
		frost::v2i32 FROST_SYSTEM getSize() const;

	private:
		frost::v2i32 _size;
	};

	// 
	// CURSOR EVENTS
	class cursorGuiEvent : public guiEvent
	{
	public:
		FROST_SYSTEM cursorGuiEvent(const frost::v2i32& position);
		frost::v2i32 FROST_SYSTEM getPosition() const;

	private:
		frost::v2i32 _position;
	};
	class cursorEnterGuiEvent : public cursorGuiEvent
	{
	public:
		FROST_SYSTEM cursorEnterGuiEvent(const frost::v2i32& position);
	};
	class cursorMoveGuiEvent : public cursorGuiEvent
	{
	public:
		FROST_SYSTEM cursorMoveGuiEvent(const frost::v2i32& position);
	};
	class cursorLeaveGuiEvent : public cursorGuiEvent
	{
	public:
		FROST_SYSTEM cursorLeaveGuiEvent(const frost::v2i32& position);
	};

	class mouseMoveGuiEvent : public guiEvent
	{
	public:
		FROST_SYSTEM mouseMoveGuiEvent(const v2i32& delta);
		FROST_SYSTEM mouseMoveGuiEvent(i32 delta_x, i32 delta_y);
		FROST_SYSTEM v2i32 getDelta() const;

	private:
		v2i32 _delta;
	};

	class scrollWheelGuiEvent : public guiEvent
	{
	public:
		FROST_SYSTEM scrollWheelGuiEvent(const v2i32& delta);
		FROST_SYSTEM scrollWheelGuiEvent(i32 delta_x, i32 delta_y);
		FROST_SYSTEM v2i32 getDelta() const;

	private:
		v2i32 _delta;
	};

	class keyGuiEvent : public guiEvent
	{
	public:
		FROST_SYSTEM keyGuiEvent(key key);
		FROST_SYSTEM key getKey() const;

	private:
		key _key;
	};
	class keyDownGuiEvent : public keyGuiEvent
	{
	public:
		FROST_SYSTEM keyDownGuiEvent(key key);
	};
	class keyUpGuiEvent : public keyGuiEvent
	{
	public:
		FROST_SYSTEM keyUpGuiEvent(key key);
	};

	//
	// OTHER EVENTS
	class redrawGuiEvent : public guiEvent
	{
	public:
		redrawGuiEvent() = default;
	};

	class closeGuiEvent : public guiEvent
	{
	public:
		closeGuiEvent() = default;
	};

	class destroyGuiEvent : public guiEvent
	{
	public:
		destroyGuiEvent() = default;
	};

	// ADDING EVENTS
	//	- Create event data class
	//	- Add Vector of relevant event handlers to gui implementation
	//	- Add interface for adding/removing event handlers (declare in )
	//	- Implement event signaling into gui procedure
	//
}
