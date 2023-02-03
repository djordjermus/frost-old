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
}
