#pragma once
namespace frost
{
	template<class T> class impl_t;
	template<class T> using pimpl_t = impl_t<T>*;

	/// <summary>
	/// Pointer to implementation
	/// Implementation may not contain any member variable aside from pimpl_t<T> inherited from the pimpl<T>
	/// </summary>
	template<class T>
	class pimpl
	{
	public:
		pimpl() :
			_pimpl() {}
		pimpl(pimpl_t<T> ptr) :
			_pimpl(ptr) {}
		pimpl(pimpl&& ptr) noexcept :
			_pimpl(ptr.detachPimpl()) {}
		pimpl& operator=(pimpl&& ptr) noexcept
		{
			swapPimpl(ptr);
			return *this;
		}

		pimpl_t<T> getPimpl() noexcept
		{
			return _pimpl;
		}

		[[nodiscard]]
		pimpl_t<T> detachPimpl() noexcept
		{
			pimpl_t<T> ret = _pimpl;
			_pimpl = nullptr;
			return ret;
		}

		[[nodiscard]]
		pimpl_t<T> swapPimpl(pimpl_t<T> swap) noexcept
		{
			pimpl_t<T> ret = _pimpl;
			_pimpl = swap;
			return ret;
		}

		void swapPimpl(pimpl<T>& swap) noexcept
		{
			pimpl_t<T> temp = _pimpl;
			_pimpl = swap._pimpl;
			swap._pimpl = temp;
		}

		void swapPimpl(pimpl<T>&& swap) noexcept
		{
			pimpl_t<T> temp = _pimpl;
			_pimpl = swap._pimpl;
			swap._pimpl = temp;
		}

		T& operator->()
		{
			return *reinterpret_cast<T*>(*this);
		}
		const T& operator->() const
		{
			return *reinterpret_cast<const T*>(*this);
		}

		pimpl(const pimpl& ptr) = delete;
		pimpl& operator=(const pimpl& ptr) = delete;

	private:
		pimpl_t<T> _pimpl;
	};
}