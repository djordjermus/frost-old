#if defined(_WIN32) || defined(_WIN64)
#include "_impl.hpp"
namespace frost::system
{
#define WM_APP_END 0xCCCC
	void message::initQueue()
	{
		MSG msg;
		::PeekMessageW(&msg, nullptr, 0, 0, PM_NOREMOVE);
	}

	template<>
	void message::send<void>(u64 target_thread, void(*procedure)(void* argument), void* argument)
	{
		if (target_thread == 0)
			throw std::invalid_argument("Failed to send message to a thread - target_thread is 0.");
		if (procedure == nullptr)
			throw std::invalid_argument("Failed to send message to a thread - procedure is null.");

		auto ret = ::PostThreadMessageW
		(
			static_cast<DWORD>(target_thread),
			WM_APP_END - 1,
			reinterpret_cast<WPARAM>(procedure),
			reinterpret_cast<LPARAM>(argument)
		);
		if (ret == FALSE)
			throw std::exception("Failed to send message to a thread.");
	}

	pimpl_t<message> message::create()
	{
		MSG* ret = new MSG();
		return reinterpret_cast<pimpl_t<message>>(ret);
	}
	pimpl_t<message> message::clone(pimpl_t<message> ptr)
	{
		MSG* ret = new MSG();
		*ret = *reinterpret_cast<MSG*>(ptr);
		return reinterpret_cast<pimpl_t<message>>(ret);
	}
	void message::waitPull(pimpl_t<message> ptr)
	{
		::GetMessageW
		(
			reinterpret_cast<MSG*>(ptr),
			nullptr,
			0,
			0
		);
	}
	void message::immediatePull(pimpl_t<message> ptr)
	{
		::PeekMessageW
		(
			reinterpret_cast<MSG*>(ptr),
			nullptr,
			0,
			0,
			PM_REMOVE
		);
	}
	void message::dispatch(pimpl_t<message> ptr)
	{
		MSG* msg = reinterpret_cast<MSG*>(ptr);
		::TranslateMessage(msg);
		::DispatchMessageW(msg);
		if (msg->message == (WM_APP_END - 1))
		{
			void(*procedure)(void*)	= reinterpret_cast<void(*)(void*)>(msg->wParam);
			void* argument			= reinterpret_cast<void*>(msg->lParam);
			procedure(argument);
		}
	}
	void message::destroy(pimpl_t<message> ptr)
	{
		if (ptr == nullptr)
			throw std::invalid_argument("Failed to destroy message - message is null");

		delete reinterpret_cast<MSG*>(ptr);
	}
}

#endif
