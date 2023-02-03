#include "frost.core/vectors.hpp"
#include "frost.core/eventData.h"
#include "frost.core/pimpl.hpp"
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
		inline cursorEnterGuiEvent(const frost::v2i32& position) :
			cursorGuiEvent(position) {}
	};
	class cursorMoveGuiEvent : public cursorGuiEvent
	{
	public:
		inline cursorMoveGuiEvent(const frost::v2i32& position) :
			cursorGuiEvent(position) {}
	};
	class cursorLeaveGuiEvent : public cursorGuiEvent
	{
	public:
		inline cursorLeaveGuiEvent(const frost::v2i32& position) :
			cursorGuiEvent(position) {}
	};



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
	//	- Create system function that signals event handlers
	//	- Add it to gui procedure
	//
}
