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
	frost::string concatenation = hello + world;
	frost::string boolean(true);
	frost::string uinteger(11222333444555666ull);
	frost::string sinteger(-1337ll);
	frost::string dbl(-1234567.456);
	std::wcout << concatenation.substring(2, 5).begin() << L'\n';
	std::wcout << boolean.begin() << L'\n';
	std::wcout << uinteger.begin() << L'\n';
	std::wcout << sinteger.begin() << L'\n';
	std::wcout << dbl.begin() << L'\n';
	return 0;

	u64 max = 1'000;
	auto th1 = frost::system::thread(printToMax, &max);
	auto th2 = frost::system::thread(printToZero, &max);
	//auto th3 = frost::system::thread(pump, (void*)nullptr);
	//sf.acquire();
	//
	//for (u64 i = 0; i < 1000; i++)
	//{
	//	frost::system::message::send(th3.getId(), printNumAndRelease, &i);
	//	sf.acquire();
	//}
}