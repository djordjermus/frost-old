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
		::WaitForSingleObject(ptr->mutex, ~0ull);
	}
	bool recmx::tryAcquire(pimpl_t<recmx> ptr)
	{
		if (ptr == nullptr) throw;
		return ::WaitForSingleObject(ptr->mutex, 0ull);
	}
	void recmx::release(pimpl_t<recmx> ptr)
	{
		if (ptr == nullptr) throw;
		::ReleaseMutex(ptr->mutex);
	}
	u64 recmx::getSpin(pimpl_t<recmx> ptr)
	{
		return ptr->spin;
	}
	void recmx::destroy(pimpl_t<recmx> ptr)
	{
		if (ptr == nullptr) throw;
		::CloseHandle(ptr->mutex);
		delete ptr;
	}
}
#endif
