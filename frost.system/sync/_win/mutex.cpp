#if defined(_WIN32) || defined(_WIN64)
#include "_impl.hpp"
namespace frost::system
{
	pimpl_t<mutex> mutex::create(bool auto_acquire)
	{
		return reinterpret_cast<pimpl_t<mutex>>(::CreateMutexW(nullptr, static_cast<BOOL>(auto_acquire), nullptr));
	}
	void mutex::acquire(pimpl_t<mutex> ptr)
	{
		if (ptr == nullptr)
			throw std::invalid_argument("Failed to acquire mutex - mutex is null.");

		DWORD result = ::WaitForSingleObject(ptr, ~0ul);
		switch (result)
		{
		break; case WAIT_FAILED:
			throw std::exception("Failed to acquire mutex.");
		break; case WAIT_TIMEOUT:
			throw std::exception("Failed to acquire mutex - Wait timeout.");
		}
	}
	bool mutex::tryAcquire(pimpl_t<mutex> ptr)
	{
		if (ptr == nullptr)
			throw std::invalid_argument("Failed to try acquire mutex - mutex is null.");

		DWORD result = ::WaitForSingleObject(ptr, 0ul);
		switch (result)
		{
		break; case WAIT_FAILED:
			throw std::exception("Failed to acquire mutex.");
		break; case WAIT_TIMEOUT:
			return false;
		break; case WAIT_OBJECT_0: case WAIT_ABANDONED:
			return true;
		}
		return false;
	}
	void mutex::release(pimpl_t<mutex> ptr)
	{
		if (ptr == nullptr)
			throw std::invalid_argument("Failed to release mutex - mutex is null.");

		if (::ReleaseMutex(ptr) == FALSE)
			throw std::exception("Failed to release mutex.");
	}
	void mutex::destroy(pimpl_t<mutex> ptr)
	{
		if (ptr == nullptr)
			throw std::invalid_argument("Failed to destroy mutex - mutex is null.");
		if (::CloseHandle(ptr) == FALSE)
			throw std::exception("Failed to destroy mutex.");
	}
}
#endif
