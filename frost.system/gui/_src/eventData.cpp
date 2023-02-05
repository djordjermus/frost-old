#include "../eventData.hpp"
namespace frost::system
{
	bool guiEvent::doDefaultAction() const
	{
		return !_prevent_default;
	}
	void guiEvent::preventDefault()
	{
		_prevent_default = true;
	}

	repositionGuiEvent::repositionGuiEvent(const frost::v2i32& position) :
		_position(position) {}
	frost::v2i32 repositionGuiEvent::getPosition() const
	{
		return _position;
	}
	resizeGuiEvent::resizeGuiEvent(const frost::v2i32& size) :
		_size(size) {}
	frost::v2i32 resizeGuiEvent::getSize() const
	{
		return _size;
	}

	cursorGuiEvent::cursorGuiEvent(const frost::v2i32& position) :
		_position(position)  {}
	frost::v2i32 cursorGuiEvent::getPosition() const
	{
		return _position;
	}
	cursorEnterGuiEvent::cursorEnterGuiEvent(const frost::v2i32& position) :
		cursorGuiEvent(position) {}
	cursorMoveGuiEvent::cursorMoveGuiEvent(const frost::v2i32& position) :
		cursorGuiEvent(position) {}
	cursorLeaveGuiEvent::cursorLeaveGuiEvent(const frost::v2i32& position) :
		cursorGuiEvent(position) {}

	mouseMoveGuiEvent::mouseMoveGuiEvent(const v2i32& delta) :
		_delta(delta) {}
	mouseMoveGuiEvent::mouseMoveGuiEvent(i32 delta_x, i32 delta_y) :
		_delta(delta_x, delta_y) {}
	v2i32 mouseMoveGuiEvent::getDelta() const
	{
		return _delta;
	}
	scrollWheelGuiEvent::scrollWheelGuiEvent(const v2i32& delta) :
		_delta(delta) {}
	scrollWheelGuiEvent::scrollWheelGuiEvent(i32 delta_x, i32 delta_y) :
		_delta(delta_x, delta_y) {}
	v2i32 scrollWheelGuiEvent::getDelta() const
	{
		return _delta;
	}

	keyGuiEvent::keyGuiEvent(key key) :
		_key(key) {}
	system::key keyGuiEvent::getKey() const
	{
		return _key;
	}
	keyDownGuiEvent::keyDownGuiEvent(key key) :
		keyGuiEvent(key) {}
	keyUpGuiEvent::keyUpGuiEvent(key key) :
		keyGuiEvent(key) {}
}
