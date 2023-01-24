#if defined(_WIN32) || defined(_WIN64)
#include "_impl.hpp"
namespace frost::system
{
	semaphore::semaphore(pimpl_t<semaphore> ptr) :
		pimpl<semaphore>(ptr) {}
	semaphore::semaphore(i32 count, i32 max) :
		semaphore(create(count, max	)) {}
	semaphore::semaphore(pimpl<semaphore>&& move) noexcept :
		semaphore(move.detachPimpl()) {}
	semaphore& semaphore::operator=(pimpl<semaphore>&& move) noexcept
	{
		swapPimpl(move);
		return *this;
	}
	semaphore::~semaphore()
	{
		if (getPimpl() != nullptr)
			destroy(getPimpl());
	}



	void semaphore::acquire()
	{
		return acquire(this->getPimpl());
	}
	bool semaphore::tryAcquire()
	{
		return tryAcquire(this->getPimpl());
	}
	void semaphore::release()
	{
		return release(this->getPimpl());
	}



	pimpl_t<semaphore> semaphore::create(i32 count, i32 max)
	{
		return reinterpret_cast<pimpl_t<semaphore>>(::CreateSemaphoreW(nullptr, count, max, nullptr));
	}
	void semaphore::acquire(pimpl_t<semaphore> ptr)
	{
		if (ptr == nullptr) throw;
		::WaitForSingleObject(ptr, ~0ull);
	}
	bool semaphore::tryAcquire(pimpl_t<semaphore> ptr)
	{
		if (ptr == nullptr) throw;
		return ::WaitForSingleObject(ptr, 0ull);
	}
	void semaphore::release(pimpl_t<semaphore> ptr)
	{
		if (ptr == nullptr) throw;
		::ReleaseSemaphore(ptr, 1, nullptr);
	}
	void semaphore::destroy(pimpl_t<semaphore> ptr)
	{
		if (ptr == nullptr) throw;
		::CloseHandle(ptr);
	}
}
#endif
