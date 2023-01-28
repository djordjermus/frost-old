#include "../string.hpp"
#include <stdexcept>
#include <math.h>
#define BUF_SIZE 121
namespace frost
{
	pimpl_t<string> string::create(const wchar_t* source)
	{
		// Calculate length
		const wchar_t* counter = source;
		while (*counter != L'\0')
			counter++;
		u64 length = static_cast<u64>(counter - source);
		
		// Allocate buffer, mark length
		wchar_t* buffer = new wchar_t[length + 5];
		reinterpret_cast<u64*>(buffer)[0] = length;

		// Copy string
		buffer = buffer + 4;
		for (u64 i = 0; i <= length; i++)
			buffer[i] = source[i];

		// Return buffer
		return reinterpret_cast<pimpl_t<string>>(buffer);
	}
	pimpl_t<string> string::create(bool value, const format& format)
	{
		return create(value ? L"true" : L"false");
	}
	pimpl_t<string> string::create(u64 value, const format& format)
	{
		if (value == 0)
			return create(L"0");

		wchar_t buffer[BUF_SIZE];
		buffer[BUF_SIZE - 1] = L'\0';
		u64 i = BUF_SIZE - 2;

		while (value != 0)
		{
			if (format.part_size != 0 && ((i + format.part_size) % (format.part_size + 1)) == format.part_size)
				buffer[i--] = format.part_separator;
			buffer[i--] = L'0' + (value % 10);
			value = value / 10;
		}

		return create(&buffer[i + 1]);
	}
	pimpl_t<string> string::create(i64 value, const format& format)
	{
		if (value == 0)
			return create(L"0");

		bool negative = value < 0;
		value = (static_cast<i64>(!negative) * value) + (static_cast<i64>(negative) * -value);

		wchar_t buffer[BUF_SIZE];
		buffer[BUF_SIZE - 1] = L'\0';
		u64 i = BUF_SIZE - 2;

		while (value != 0)
		{
			if (format.part_size != 0 && ((i + format.part_size) % (format.part_size + 1)) == format.part_size)
				buffer[i--] = format.part_separator;
			buffer[i--] = L'0' + (value % 10);
			value = value / 10;
		}

		buffer[i] = L'-';
		return create(&buffer[i + 1 - negative]);
	}
	pimpl_t<string> string::create(f64 value, const format& format)
	{
		i64 decimal = fmod(value, 1.0) * 1'000'000'000'000'000'000;
		decimal = (decimal >= 0) * decimal + (decimal < 0) * -decimal;

		wchar_t buffer[BUF_SIZE];
		buffer[BUF_SIZE - 1] = L'\0';
		u64 i = BUF_SIZE - 2;

		// Remove leading zeroes from decimal part
		while ((decimal % 10) == 0)
			decimal = decimal / 10;

		// Write decimal part
		u64 precision = format.precision == 0 ? ~0ull : format.precision;
		while (decimal != 0 && precision != 0)
		{
			buffer[i--]	= L'0' + (decimal % 10);
			decimal		= decimal / 10;
			precision--;
		}

		// Decimal dot
		buffer[i--] = format.decimal_separator;
		u64 i_off = BUF_SIZE - 2 - i;

		i64 whole = static_cast<i64>(value);

		bool negative = whole < 0;
		whole = (static_cast<i64>(!negative) * whole) + (static_cast<i64>(negative) * -whole);

		while (whole != 0)
		{
			if (format.part_size != 0 && (((i + i_off) + format.part_size) % (format.part_size + 1)) == format.part_size)
				buffer[i--] = format.part_separator;
			buffer[i--] = L'0' + (whole % 10);
			whole = whole / 10;
		}
		buffer[i] = L'-';

		return create(&buffer[i + 1 - negative]);
	}
	pimpl_t<string> string::clone(pimpl_t<string> ptr)
	{
		// Calculate length
		u64 length = getLength(ptr);
		
		// Allocate buffer, mark length
		wchar_t* buffer = new wchar_t[length + 5];
		reinterpret_cast<u64*>(buffer)[0] = length;

		// Copy string
		buffer = buffer + 4;
		for (u64 i = 0; i <= length; i++)
			buffer[i] = reinterpret_cast<const wchar_t*>(ptr)[i];

		// Return buffer
		return reinterpret_cast<pimpl_t<string>>(buffer);
	}
	pimpl_t<string> string::concat(pimpl_t<string> left, pimpl_t<string> right)
	{
		// Calculate length
		u64 left_len = getLength(left);
		u64 right_len = getLength(right);
		u64 length = left_len + right_len;

		// Allocate buffer, mark length
		wchar_t* buffer = new wchar_t[length + 5];
		reinterpret_cast<u64*>(buffer)[0] = length;

		// Copy strings
		buffer = buffer + 4;
		wchar_t* write = buffer;
		for (u64 i = 0; i < left_len; i++)
			write[i] = reinterpret_cast<const wchar_t*>(left)[i];
		write = write + left_len;
		for (u64 i = 0; i <= right_len; i++)
			write[i] = reinterpret_cast<const wchar_t*>(right)[i];

		// Return buffer
		return reinterpret_cast<pimpl_t<string>>(buffer);
	}
	pimpl_t<string> string::substring(pimpl_t<string> ptr, u64 start, u64 length)
	{
		if (ptr == nullptr)
			throw std::invalid_argument("Failed to construct a substring - string is null.");

		if ((start + length) > getLength(ptr))
			throw std::invalid_argument("Failed to construct a substring - substring range is out of bounds.");

		if (length == 0)
			return create(L"\0");

		// Allocate buffer, mark length
		wchar_t* buffer = new wchar_t[length + 5];
		reinterpret_cast<u64*>(buffer)[0] = length;

		// Copy string
		buffer	= buffer + 4;
		u64 i = 0;
		for (i; i < length; i++)
			buffer[i] = reinterpret_cast<const wchar_t*>(ptr)[start + i];
		buffer[i] = L'\0';
		// Return buffer
		return reinterpret_cast<pimpl_t<string>>(buffer);
		
	}

	const wchar_t* string::getData(pimpl_t<string> ptr)
	{
		return reinterpret_cast<const wchar_t*>(ptr);
	}
	u64 string::getLength(pimpl_t<string> ptr)
	{
		return *(reinterpret_cast<const u64*>(ptr) - 1ull);
	}
	void string::destroy(pimpl_t<string> ptr)
	{
		delete (reinterpret_cast<const wchar_t*>(ptr) - 4ull);
	}
}