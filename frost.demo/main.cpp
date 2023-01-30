#include <iostream>
#include <mutex>
#include "frost.core/_include.hpp"
#include "frost.system/_include.hpp"
frost::system::semaphore sf(0, 1);
void pump(void* unused)
{
	frost::system::message::initQueue();
	sf.release();
	frost::system::message msg;
	while (true)
	{
		msg.waitPull();
		msg.dispatch();
	}

}
void printNumAndRelease(u64* pNum)
{
	std::cout << *pNum << '\n';
	sf.release();
}
void printToMax(u64* pMax)
{
	for (u64 i = 0ull; i < *pMax; i++)
		std::cout << i << '\n';
}
void printToZero(u64* pFrom)
{
	for (u64 i = 0ull; i <= *pFrom; i++)
		std::cout << (*pFrom - i) << '\n';
}
int main()
{
	frost::system::message::initQueue();
	frost::system::message msg;

	frost::system::gui::description desc = {};
	auto gui = frost::system::gui(desc);
	while (gui.isAlive())
	{
		msg.waitPull();
		msg.dispatch();
	}
}