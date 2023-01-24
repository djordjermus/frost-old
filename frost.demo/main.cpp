#include <iostream>
#include <mutex>
#include "frost.system/_include.hpp"
int main()
{
	frost::system::semaphore sf(5, 10);
	sf.acquire();
	sf.acquire();
	sf.acquire();
	sf.acquire();
	sf.acquire();
	//sf.acquire();
	std::printf("Hello, %s", "World");
}