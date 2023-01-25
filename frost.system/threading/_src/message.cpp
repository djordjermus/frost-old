#if defined(_WIN32) || defined(_WIN64)
#include "_impl.hpp"
namespace frost::system
{
	void message::initQueue()
	{
		MSG msg;
		::PeekMessageW(&msg, nullptr, 0, 0, PM_NOREMOVE);
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
	void message::destroy(pimpl_t<message> ptr)
	{
		if (ptr == nullptr)
			throw std::invalid_argument("Failed to destroy message - message is null");

		delete reinterpret_cast<MSG*>(ptr);
	}
}

#endif
