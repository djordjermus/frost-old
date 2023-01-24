#include "../mutex.hpp"

#if defined(_WIN32) || defined(_WIN64)
#include <Windows.h>
namespace frost::system
{
	mutex::mutex(pimpl_t<mutex> ptr) :
		pimpl<mutex>(ptr) {}
	mutex::mutex(bool auto_acquire) :
		mutex(create(auto_acquire)) {}
	mutex::mutex(pimpl<mutex>&& move) noexcept :
		mutex(move.detachPimpl()) {}
	mutex& mutex::operator=(pimpl<mutex>&& move) noexcept
	{
		swapPimpl(move);
		return *this;
	}
	mutex::~mutex()
	{
		if (this->getPimpl())
			destroy(this->getPimpl());
	}

	void mutex::acquire()
	{
		return acquire(this->getPimpl());
	}
	bool mutex::tryAcquire()
	{
		return tryAcquire(this->getPimpl());
	}
	void mutex::release()
	{
		return release(this->getPimpl());
	}

	pimpl_t<mutex> mutex::create(bool auto_acquire)
	{
		return reinterpret_cast<pimpl_t<mutex>>(::CreateMutexW(nullptr, static_cast<BOOL>(auto_acquire), nullptr);
	}
	void mutex::acquire(pimpl_t<mutex> ptr)
	{
		if (ptr == nullptr) throw;
		::WaitForSingleObject(ptr, ~0ull);
	}
	bool mutex::tryAcquire(pimpl_t<mutex> ptr)
	{
		if (ptr == nullptr) throw;
		return ::WaitForSingleObject(ptr, 0ull);
	}
	void mutex::release(pimpl_t<mutex> ptr)
	{
		if (ptr == nullptr) throw;
		::ReleaseMutex(ptr);
	}
	void mutex::destroy(pimpl_t<mutex> ptr)
	{
		if (ptr == nullptr) throw;
		::CloseHandle(ptr);
	}
}
#endif
