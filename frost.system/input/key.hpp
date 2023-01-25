#include "frost.core/primitives.hpp"
#include "frost.core/pimpl.hpp"
#include "../_macro.hpp"
#pragma once
namespace frost::system {

	class key final : public frost::pimpl<key> 
	{
	public:

		inline key(pimpl_t<key> ptr) :
			pimpl<key>(ptr) {}
		inline key() :
			key(nullkey) {}
		inline key(const key& copy) :
			key(copy.getPimpl()) {}
		inline key(const key&& copy) noexcept :
			key(copy.getPimpl()) {}
		inline key& operator=(const key& copy)
		{
			(void)swapPimpl(clone(copy.getPimpl()));
			return *this;
		}
		inline key& operator=(const key&& copy) noexcept
		{
			(void)swapPimpl(clone(copy.getPimpl()));
			return *this;
		}

		static FROST_SYSTEM pimpl_t<key> clone(pimpl_t<key> ptr);

		static FROST_SYSTEM const key nullkey;

		static FROST_SYSTEM const key left_mouse_button;
		static FROST_SYSTEM const key right_mouse_button;
		static FROST_SYSTEM const key middle_mouse_button;
		static FROST_SYSTEM const key x1_mouse_button;
		static FROST_SYSTEM const key x2_mouse_button;

		static FROST_SYSTEM const key backspace;
		static FROST_SYSTEM const key tab;

		static FROST_SYSTEM const key clear;
		static FROST_SYSTEM const key enter;

		static FROST_SYSTEM const key pause;
		static FROST_SYSTEM const key ime_kana;
		static FROST_SYSTEM const key ime_hangul;
		static FROST_SYSTEM const key ime_hanguel;
		static FROST_SYSTEM const key ime_on;
		static FROST_SYSTEM const key ime_final;
		static FROST_SYSTEM const key ime_hanja;
		static FROST_SYSTEM const key ime_kanji;
		static FROST_SYSTEM const key ime_off;

		static FROST_SYSTEM const key escape;
		static FROST_SYSTEM const key ime_convert;
		static FROST_SYSTEM const key ime_nonconvert;
		static FROST_SYSTEM const key ime_accept;
		static FROST_SYSTEM const key ime_mode_change;

		static FROST_SYSTEM const key space;
		static FROST_SYSTEM const key page_up;
		static FROST_SYSTEM const key page_down;
		static FROST_SYSTEM const key end;
		static FROST_SYSTEM const key home;

		static FROST_SYSTEM const key backspace;
		static FROST_SYSTEM const key tab;

		static FROST_SYSTEM const key left_arrow;
		static FROST_SYSTEM const key up_arrow;
		static FROST_SYSTEM const key right_arrow;
		static FROST_SYSTEM const key down_arrow;

		static FROST_SYSTEM const key select;
		static FROST_SYSTEM const key print;
		static FROST_SYSTEM const key execute;
		static FROST_SYSTEM const key print_screen;
		static FROST_SYSTEM const key ins;
		static FROST_SYSTEM const key del;
		static FROST_SYSTEM const key help;

		static FROST_SYSTEM const key alpha0;
		static FROST_SYSTEM const key alpha1;
		static FROST_SYSTEM const key alpha2;
		static FROST_SYSTEM const key alpha3;
		static FROST_SYSTEM const key alpha4;
		static FROST_SYSTEM const key alpha5;
		static FROST_SYSTEM const key alpha6;
		static FROST_SYSTEM const key alpha7;
		static FROST_SYSTEM const key alpha8;
		static FROST_SYSTEM const key alpha9;

		static FROST_SYSTEM const key a;
		static FROST_SYSTEM const key b;
		static FROST_SYSTEM const key c;
		static FROST_SYSTEM const key d;
		static FROST_SYSTEM const key e;
		static FROST_SYSTEM const key f;
		static FROST_SYSTEM const key g;
		static FROST_SYSTEM const key h;
		static FROST_SYSTEM const key i;
		static FROST_SYSTEM const key j;
		static FROST_SYSTEM const key k;
		static FROST_SYSTEM const key l;
		static FROST_SYSTEM const key m;
		static FROST_SYSTEM const key n;
		static FROST_SYSTEM const key o;
		static FROST_SYSTEM const key p;
		static FROST_SYSTEM const key q;
		static FROST_SYSTEM const key r;
		static FROST_SYSTEM const key s;
		static FROST_SYSTEM const key t;
		static FROST_SYSTEM const key u;
		static FROST_SYSTEM const key v;
		static FROST_SYSTEM const key w;
		static FROST_SYSTEM const key x;
		static FROST_SYSTEM const key y;
		static FROST_SYSTEM const key z;
		
		static FROST_SYSTEM const key left_win;
		static FROST_SYSTEM const key right_win;
		static FROST_SYSTEM const key apps;

		static FROST_SYSTEM const key numpad0;
		static FROST_SYSTEM const key numpad1;
		static FROST_SYSTEM const key numpad2;
		static FROST_SYSTEM const key numpad3;
		static FROST_SYSTEM const key numpad4;
		static FROST_SYSTEM const key numpad5;
		static FROST_SYSTEM const key numpad6;
		static FROST_SYSTEM const key numpad7;
		static FROST_SYSTEM const key numpad8;
		static FROST_SYSTEM const key numpad9;
		static FROST_SYSTEM const key multiply;
		static FROST_SYSTEM const key add;
		static FROST_SYSTEM const key separator;
		static FROST_SYSTEM const key subtract;
		static FROST_SYSTEM const key decimal;
		static FROST_SYSTEM const key divide;

		static FROST_SYSTEM const key f1;
		static FROST_SYSTEM const key f2;
		static FROST_SYSTEM const key f3;
		static FROST_SYSTEM const key f4;
		static FROST_SYSTEM const key f5;
		static FROST_SYSTEM const key f6;
		static FROST_SYSTEM const key f7;
		static FROST_SYSTEM const key f8;
		static FROST_SYSTEM const key f9;
		static FROST_SYSTEM const key f10;
		static FROST_SYSTEM const key f11;
		static FROST_SYSTEM const key f12;
		static FROST_SYSTEM const key f13;
		static FROST_SYSTEM const key f14;
		static FROST_SYSTEM const key f15;
		static FROST_SYSTEM const key f16;
		static FROST_SYSTEM const key f17;
		static FROST_SYSTEM const key f18;
		static FROST_SYSTEM const key f19;
		static FROST_SYSTEM const key f20;
		static FROST_SYSTEM const key f21;
		static FROST_SYSTEM const key f22;
		static FROST_SYSTEM const key f23;
		static FROST_SYSTEM const key f24;

		static FROST_SYSTEM const key number_lock;
		static FROST_SYSTEM const key scroll_lock;
		static FROST_SYSTEM const key left_shift;
		static FROST_SYSTEM const key right_shift;
		static FROST_SYSTEM const key left_control;
		static FROST_SYSTEM const key right_control;
		static FROST_SYSTEM const key left_alt;
		static FROST_SYSTEM const key right_alt;

		static FROST_SYSTEM const key plus;
		static FROST_SYSTEM const key comma;
		static FROST_SYSTEM const key minus;
		static FROST_SYSTEM const key period;
		static FROST_SYSTEM const key slash;
		static FROST_SYSTEM const key tilde;
		static FROST_SYSTEM const key open_square_bracket;
		static FROST_SYSTEM const key back_slash;
		static FROST_SYSTEM const key close_square_bracket;
		static FROST_SYSTEM const key quote;
	};
}