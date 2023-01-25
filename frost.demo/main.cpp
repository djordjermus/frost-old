#include <iostream>
#include <mutex>
#include "frost.system/_include.hpp"
int main()
{
	frost::system::key k = frost::system::key::add;
	auto k2 = k;
}