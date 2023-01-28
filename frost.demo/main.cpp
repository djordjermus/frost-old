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
	frost::string hello(L"Hello ");
	frost::string world(L"World!");
	frost::string strings[] =
	{
		hello + world,
		frost::string(false),
		frost::string(123456789ull),
		frost::string(-1234567890ll),
		frost::string(-12345.67890),
	};
	for(auto& str : strings)
		std::wcout << str.begin()  << L'\n';
	return 0;

	u64 max = 1'000;
	auto th1 = frost::system::thread(printToMax, &max);
	auto th2 = frost::system::thread(printToZero, &max);
}