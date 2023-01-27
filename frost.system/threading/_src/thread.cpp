#include "_impl.hpp"
#if defined(_WIN32) || defined(_WIN64)
namespace frost::system
{
	struct threadInitData { void(*procedure)(void*); void* argument; };
	static unsigned long sysThreadProc(void* data);

	u64 thread::getCallerId()
	{
		return static_cast<u64>(::GetCurrentThreadId());
	}
	template<>
	frost::pimpl_t<thread> thread::create<void>(void(*procedure)(void*), void* argument)
	{
		threadInitData* data = new threadInitData();
		data->procedure = procedure;
		data->argument = argument;

		HANDLE th = ::CreateThread
		(
			nullptr,
			0ull,
			sysThreadProc,
			data,
			0,
			nullptr
		);

		return reinterpret_cast<frost::pimpl_t<thread>>(th);
	}
	bool thread::isRunning(frost::pimpl_t<thread> ptr)
	{
		if (ptr == nullptr)
			throw std::invalid_argument("Failed to get thread state - thread is null.");
		return ::WaitForSingleObject(ptr, 0ul) == WAIT_TIMEOUT;
	}
	bool thread::isJoinable(frost::pimpl_t<thread> ptr)
	{
		if (ptr == nullptr)
			throw std::invalid_argument("Failed to get thread state - thread is null.");
		return isRunning(ptr) && ::GetCurrentThreadId() != ::GetThreadId(ptr);
	}
	u64 thread::getId(frost::pimpl_t<thread> ptr)
	{
		if (ptr == nullptr)
			throw std::invalid_argument("Failed to get thread id - thread is null.");
		return static_cast<u64>(::GetThreadId(ptr));
	}
	void thread::join(frost::pimpl_t<thread> ptr)
	{
		if (ptr == nullptr)
			throw std::invalid_argument("Failed to join thread - thread is null.");
		if (::GetCurrentThreadId() == ::GetThreadId(ptr))
			throw std::exception("Failed to join thread - caller is the same thread as join thread.");
		DWORD result = ::WaitForSingleObject(ptr, ~0ul);
		switch (result)
		{
		case WAIT_TIMEOUT:
		case WAIT_FAILED:
			throw std::exception("Failed to join thread.");
		}
	}
	static unsigned long sysThreadProc(void* ptr)
	{
		threadInitData* data = reinterpret_cast<threadInitData*>(ptr);
		data->procedure(data->argument);
		delete data;
		return 0;
	}
}
#endif
