#include "primitives.hpp"
#include "pimpl.hpp"
#pragma once
namespace frost
{
	class string final : public frost::pimpl<string>
	{
	public:
		struct format;

		inline string(pimpl_t<string> ptr) :
			frost::pimpl<string>(ptr) {}
		inline string(const wchar_t* source) :
			string(create(source)) {}
		inline string(bool value, const format& format = format()) :
			string(create(value)) {}
		inline string(u64 value, const format& format = format()) :
			string(create(value)) {}
		inline string(i64 value, const format& format = format()) :
			string(create(value)) {}
		inline string(f64 value, const format& format = format()) :
			string(create(value)) {}
		inline string(const string& copy) :
			string(clone(copy.getPimpl())) {}
		inline string(const string&& copy) noexcept :
			string(clone(copy.getPimpl())) {}
		inline string(string&& move) noexcept :
			string(move.detachPimpl()) {}
		inline string& operator=(const string& copy)
		{
			if (getPimpl() != nullptr)
				destroy(getPimpl());
			(void)swapPimpl(clone(copy.getPimpl()));
			return *this;
		}
		inline string& operator=(const string&& copy) noexcept
		{
			if (getPimpl() != nullptr)
				destroy(getPimpl());
			(void)swapPimpl(clone(copy.getPimpl()));
			return *this;
		}
		inline string& operator=(string&& move) noexcept
		{
			this->swapPimpl(move);
			return *this;
		}
		inline ~string()
		{
			if (getPimpl() != nullptr)
				destroy(getPimpl());
		}

		inline string operator+(const string& right) const
		{
			return string(concat(getPimpl(), right.getPimpl()));
		}
		inline string substring(u64 start, u64 length)
		{
			return string(substring(getPimpl(), start, length));
		}

		inline const wchar_t* begin() const { return getData(getPimpl()); }
		inline const wchar_t* end() const { return getData(getPimpl()) + getLength(getPimpl()); }

		static pimpl_t<string> create(const wchar_t* source);
		static pimpl_t<string> create(bool value, const format& format = format());
		static pimpl_t<string> create(u64 value, const format& format = format());
		static pimpl_t<string> create(i64 value, const format& format = format());
		static pimpl_t<string> create(f64 value, const format& format = format());
		static pimpl_t<string> clone(pimpl_t<string> ptr);
		static pimpl_t<string> concat(pimpl_t<string> left, pimpl_t<string> right);
		static pimpl_t<string> substring(pimpl_t<string> ptr, u64 start, u64 length);
		static const wchar_t* getData(pimpl_t<string> ptr);
		static u64 getLength(pimpl_t<string> ptr);
		static void destroy(pimpl_t<string> ptr);

		struct format
		{
			wchar_t decimal_separator	= L'.';
			wchar_t part_separator		= L'\'';
			u64		part_size			= 3;
			u64		precision			= 0; // TODO
		};
	};
}