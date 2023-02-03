#include <iostream>
#include <mutex>
#include "frost.core/_include.hpp"
#include "frost.system/_include.hpp"
frost::system::semaphore sf(0, 1);
class handler :
	public frost::system::gui::repositionHandler,
	public frost::system::gui::resizeHandler,
	public frost::system::gui::redrawHandler,
	public frost::system::gui::cursorEnterHandler,
	public frost::system::gui::cursorMoveHandler,
	public frost::system::gui::cursorLeaveHandler,
	public frost::system::gui::closeHandler,
	public frost::system::gui::destroyHandler
{
	void handle(frost::pimpl_t<frost::system::gui> sender, frost::system::repositionGuiEvent& e) override;
	void handle(frost::pimpl_t<frost::system::gui> sender, frost::system::resizeGuiEvent& e) override;
	void handle(frost::pimpl_t<frost::system::gui> sender, frost::system::redrawGuiEvent& e) override;
	void handle(frost::pimpl_t<frost::system::gui> sender, frost::system::cursorEnterGuiEvent& e) override;
	void handle(frost::pimpl_t<frost::system::gui> sender, frost::system::cursorMoveGuiEvent& e) override;
	void handle(frost::pimpl_t<frost::system::gui> sender, frost::system::cursorLeaveGuiEvent& e) override;
	void handle(frost::pimpl_t<frost::system::gui> sender, frost::system::closeGuiEvent& e) override;
	void handle(frost::pimpl_t<frost::system::gui> sender, frost::system::destroyGuiEvent& e) override;
};
int main()
{
	frost::system::message::initQueue();
	frost::system::message msg;

	handler h;

	frost::system::gui::description desc = {};
	auto gui = frost::system::gui(desc);
	gui.addHandler((frost::system::gui::repositionHandler&)h);
	gui.addHandler((frost::system::gui::resizeHandler&)h);
	gui.addHandler((frost::system::gui::redrawHandler&)h);
	gui.addHandler((frost::system::gui::cursorEnterHandler&)h);
	gui.addHandler((frost::system::gui::cursorMoveHandler&)h);
	gui.addHandler((frost::system::gui::cursorLeaveHandler&)h);
	gui.addHandler((frost::system::gui::closeHandler&)h);
	gui.addHandler((frost::system::gui::destroyHandler&)h);

	while (gui.isAlive())
	{
		msg.waitPull();
		msg.dispatch();
	}
}

void handler::handle(frost::pimpl_t<frost::system::gui> sender, frost::system::repositionGuiEvent& e)
{
	std::cout << "Repositioned: " << e.getPosition().x << ", " << e.getPosition().y << '\n';
}
void handler::handle(frost::pimpl_t<frost::system::gui> sender, frost::system::resizeGuiEvent& e)
{
	std::cout << "Resized:      " << e.getSize().x << ", " << e.getSize().y << '\n';
}
void handler::handle(frost::pimpl_t<frost::system::gui> sender, frost::system::redrawGuiEvent& e)
{
	std::cout << "Redraw!\n";
}
void handler::handle(frost::pimpl_t<frost::system::gui> sender, frost::system::cursorEnterGuiEvent& e)
{
	std::cout << "MOUSE ENTER: " << e.getPosition().x << ", " << e.getPosition().y << '\n';
}
void handler::handle(frost::pimpl_t<frost::system::gui> sender, frost::system::cursorMoveGuiEvent& e)
{
	std::cout << "MOUSE MOVE:  " << e.getPosition().x << ", " << e.getPosition().y << '\n';
}
void handler::handle(frost::pimpl_t<frost::system::gui> sender, frost::system::cursorLeaveGuiEvent& e)
{
	std::cout << "MOUSE LEAVE: " << e.getPosition().x << ", " << e.getPosition().y << '\n';
}
void handler::handle(frost::pimpl_t<frost::system::gui> sender, frost::system::closeGuiEvent& e)
{
	std::cout << "Closed!\n";
}
void handler::handle(frost::pimpl_t<frost::system::gui> sender, frost::system::destroyGuiEvent& e)
{
	std::cout << "Destroyed!\n";
}