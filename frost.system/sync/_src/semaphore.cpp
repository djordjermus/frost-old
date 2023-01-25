#if defined(_WIN32) || defined(_WIN64)
#include "_impl.hpp"
namespace frost::system
{
	pimpl_t<semaphore> semaphore::create(i32 count, i32 max)
	{
		return reinterpret_cast<pimpl_t<semaphore>>(::CreateSemaphoreW(nullptr, count, max, nullptr));
	}
	void semaphore::acquire(pimpl_t<semaphore> ptr)
	{
		if (ptr == nullptr)
			throw std::invalid_argument("Field to acquite semaphore - semaphore is null.");
		
		DWORD result = ::WaitForSingleObject(ptr, ~0ul);
		switch (result)
		{
		break; case WAIT_FAILED:
			throw std::exception("Failed to acquire semaphore.");
		break; case WAIT_TIMEOUT:
			throw std::exception("Failed to acquire semaphore - Wait timeout.");
		}
	}
	bool semaphore::tryAcquire(pimpl_t<semaphore> ptr)
	{
		if (ptr == nullptr)
			throw std::invalid_argument("Field to try acquite semaphore - semaphore is null.");
		
		DWORD result = ::WaitForSingleObject(ptr, 0ul);
		switch (result)
		{
		break; case WAIT_FAILED:
			throw std::exception("Failed to acquire semaphore.");
		break; case WAIT_TIMEOUT:
			return false;
		break; case WAIT_OBJECT_0: case WAIT_ABANDONED:
			return true;
		}
		return false;
	}
	void semaphore::release(pimpl_t<semaphore> ptr)
	{
		if (ptr == nullptr)
			throw std::invalid_argument("Failed to release semaphore - semaphore is null.");

		if (::ReleaseSemaphore(ptr, 1, nullptr) == FALSE) 
			throw std::exception("Failed to release semaphore.");
	}
	void semaphore::destroy(pimpl_t<semaphore> ptr)
	{
		if (ptr == nullptr)
			throw std::invalid_argument("Failed to destroy semaphore - semaphore is null.");

		if (::CloseHandle(ptr) == FALSE)
			throw std::exception("Failed to destroy semaphore.");
	}
}
#endif
