#if defined(_WIN32) || defined(_WIN64)
#include "_impl.hpp"
namespace frost::system
{
	recmx::recmx(pimpl_t<recmx> ptr) :
		pimpl<recmx>(ptr) {}
	recmx::recmx(bool auto_acquire) :
		recmx(create(auto_acquire)) {}
	recmx::recmx(pimpl<recmx>&& move) noexcept :
		recmx(move.detachPimpl()) {}
	recmx& recmx::operator=(pimpl<recmx>&& move) noexcept
	{
		swapPimpl(move);
		return *this;
	}
	recmx::~recmx()
	{
		if (this->getPimpl())
			destroy(this->getPimpl());
	}



	void recmx::acquire()
	{
		return acquire(this->getPimpl());
	}
	bool recmx::tryAcquire()
	{
		return tryAcquire(this->getPimpl());
	}
	void recmx::release()
	{
		return release(this->getPimpl());
	}
	u64 recmx::getSpin()
	{
		return getSpin(this->getPimpl());
	}



	pimpl_t<recmx> recmx::create(bool auto_acquire)
	{
		pimpl_t<recmx> ret = new impl_t<recmx>();
		ret->mutex	= reinterpret_cast<pimpl_t<recmx>>(::CreateMutexW(nullptr, static_cast<BOOL>(auto_acquire), nullptr));
		ret->spin	= 0;
		return ret;
	}
	void recmx::acquire(pimpl_t<recmx> ptr)
	{
		if (ptr == nullptr) throw;

		DWORD result = ::WaitForSingleObject(ptr->mutex, ~0ul);
		switch (result)
		{
		break; case WAIT_FAILED:
			throw std::exception("Failed to acquire recursive mutex.");
		break; case WAIT_TIMEOUT:
			throw std::exception("Failed to acquire recursive mutex - Wait timeout.");
		break; case WAIT_OBJECT_0: case WAIT_ABANDONED:
			ptr->spin++;
		}
	}
	bool recmx::tryAcquire(pimpl_t<recmx> ptr)
	{
		if (ptr == nullptr) throw;

		DWORD result = ::WaitForSingleObject(ptr->mutex, 0ul);
		switch (result)
		{
		break; case WAIT_FAILED:
			throw std::exception("Failed to acquire recursive mutex.");
		break; case WAIT_TIMEOUT:
			return false;
		break; case WAIT_OBJECT_0: case WAIT_ABANDONED:
			ptr->spin++;
			return true;
		}
		return false;
	}

	void recmx::release(pimpl_t<recmx> ptr)
	{
		if (ptr == nullptr)
			throw std::exception("Failed to release recursive mutex - recursive mutex is null.");

		DWORD result = ::WaitForSingleObject(ptr->mutex, 0ul);
		if (result == WAIT_OBJECT_0)
		{
			ptr->spin--;
			if (ptr->spin != 0)
				return;
			else if (::ReleaseMutex(ptr->mutex) == FALSE)
				throw std::exception("Failed to release recursive mutex.");
		}
		else
			throw std::exception("Failed to release recursive mutex.");
	}
	u64 recmx::getSpin(pimpl_t<recmx> ptr)
	{
		if (ptr == nullptr)
			throw std::exception("Failed to get spin - recursive mutex is null.");
		return ptr->spin;
	}
	void recmx::destroy(pimpl_t<recmx> ptr)
	{
		if (ptr == nullptr)
			throw std::exception("Failed to destroy recursive mutex - recursive mutex is null.");

		if (::CloseHandle(ptr->mutex) == FALSE)
			throw std::exception("Failed to destroy recursive mutex.");

		delete ptr;
	}
}
#endif
