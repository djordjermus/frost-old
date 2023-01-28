#if defined(_WIN32) || defined(_WIN64)

#include <Windows.h>
#include "../key.hpp"

namespace frost::system
{
	pimpl_t<key> key::clone(pimpl_t<key> core)
	{
		return core;
	}


	const key key::nullkey				((pimpl_t<key>)(nullptr));

	const key key::left_mouse_button	((pimpl_t<key>)(0x01));
	const key key::right_mouse_button	((pimpl_t<key>)(0x02));
	const key key::middle_mouse_button	((pimpl_t<key>)(0x04));
	const key key::x1_mouse_button		((pimpl_t<key>)(0x05));
	const key key::x2_mouse_button		((pimpl_t<key>)(0x06));

	const key key::backspace			((pimpl_t<key>)(0x08));
	const key key::tab					((pimpl_t<key>)(0x09));

	const key key::clear				((pimpl_t<key>)(0x0C));
	const key key::enter				((pimpl_t<key>)(0x0D));

	const key key::pause				((pimpl_t<key>)(0x13));
	const key key::ime_kana				((pimpl_t<key>)(0x15));
	const key key::ime_hangul			((pimpl_t<key>)(0x15));
	const key key::ime_hanguel			((pimpl_t<key>)(0x15));
	const key key::ime_on				((pimpl_t<key>)(0x16));
	const key key::ime_final			((pimpl_t<key>)(0x18));
	const key key::ime_hanja			((pimpl_t<key>)(0x19));
	const key key::ime_kanji			((pimpl_t<key>)(0x19));
	const key key::ime_off				((pimpl_t<key>)(0x1A));

	const key key::escape				((pimpl_t<key>)(0x1B));
	const key key::ime_convert			((pimpl_t<key>)(0x1C));
	const key key::ime_nonconvert		((pimpl_t<key>)(0x1D));
	const key key::ime_accept			((pimpl_t<key>)(0x1E));
	const key key::ime_mode_change		((pimpl_t<key>)(0x1F));

	const key key::space				((pimpl_t<key>)(0x20));
	const key key::page_up				((pimpl_t<key>)(0x21));
	const key key::page_down			((pimpl_t<key>)(0x22));
	const key key::end					((pimpl_t<key>)(0x23));
	const key key::home					((pimpl_t<key>)(0x24));
	
	const key key::left_arrow			((pimpl_t<key>)(0x25));
	const key key::up_arrow				((pimpl_t<key>)(0x26));
	const key key::right_arrow			((pimpl_t<key>)(0x27));
	const key key::down_arrow			((pimpl_t<key>)(0x28));
	
	const key key::select				((pimpl_t<key>)(0x29));
	const key key::print				((pimpl_t<key>)(0x2A));
	const key key::execute				((pimpl_t<key>)(0x2B));
	const key key::print_screen			((pimpl_t<key>)(0x2C));
	const key key::ins					((pimpl_t<key>)(0x2D));
	const key key::del					((pimpl_t<key>)(0x2E));
	const key key::help					((pimpl_t<key>)(0x2F));

	const key key::alpha0				((pimpl_t<key>)(0x30));
	const key key::alpha1				((pimpl_t<key>)(0x31));
	const key key::alpha2				((pimpl_t<key>)(0x32));
	const key key::alpha3				((pimpl_t<key>)(0x33));
	const key key::alpha4				((pimpl_t<key>)(0x34));
	const key key::alpha5				((pimpl_t<key>)(0x35));
	const key key::alpha6				((pimpl_t<key>)(0x36));
	const key key::alpha7				((pimpl_t<key>)(0x37));
	const key key::alpha8				((pimpl_t<key>)(0x38));
	const key key::alpha9				((pimpl_t<key>)(0x39));

	const key key::a					((pimpl_t<key>)(0x41));
	const key key::b					((pimpl_t<key>)(0x42));
	const key key::c					((pimpl_t<key>)(0x43));
	const key key::d					((pimpl_t<key>)(0x44));
	const key key::e					((pimpl_t<key>)(0x45));
	const key key::f					((pimpl_t<key>)(0x46));
	const key key::g					((pimpl_t<key>)(0x47));
	const key key::h					((pimpl_t<key>)(0x48));
	const key key::i					((pimpl_t<key>)(0x49));
	const key key::j					((pimpl_t<key>)(0x4A));
	const key key::k					((pimpl_t<key>)(0x4B));
	const key key::l					((pimpl_t<key>)(0x4C));
	const key key::m					((pimpl_t<key>)(0x4D));
	const key key::n					((pimpl_t<key>)(0x4E));
	const key key::o					((pimpl_t<key>)(0x4F));
	const key key::p					((pimpl_t<key>)(0x50));
	const key key::q					((pimpl_t<key>)(0x51));
	const key key::r					((pimpl_t<key>)(0x52));
	const key key::s					((pimpl_t<key>)(0x53));
	const key key::t					((pimpl_t<key>)(0x54));
	const key key::u					((pimpl_t<key>)(0x55));
	const key key::v					((pimpl_t<key>)(0x56));
	const key key::w					((pimpl_t<key>)(0x57));
	const key key::x					((pimpl_t<key>)(0x58));
	const key key::y					((pimpl_t<key>)(0x59));
	const key key::z					((pimpl_t<key>)(0x5A));

	const key key::left_win				((pimpl_t<key>)(0x5B));
	const key key::right_win			((pimpl_t<key>)(0x5C));
	const key key::apps					((pimpl_t<key>)(0x5D));

	const key key::numpad0				((pimpl_t<key>)(0x60));
	const key key::numpad1				((pimpl_t<key>)(0x61));
	const key key::numpad2				((pimpl_t<key>)(0x62));
	const key key::numpad3				((pimpl_t<key>)(0x63));
	const key key::numpad4				((pimpl_t<key>)(0x64));
	const key key::numpad5				((pimpl_t<key>)(0x65));
	const key key::numpad6				((pimpl_t<key>)(0x66));
	const key key::numpad7				((pimpl_t<key>)(0x67));
	const key key::numpad8				((pimpl_t<key>)(0x68));
	const key key::numpad9				((pimpl_t<key>)(0x69));
	const key key::multiply				((pimpl_t<key>)(0x6A));
	const key key::add					((pimpl_t<key>)(0x6B));
	const key key::separator			((pimpl_t<key>)(0x6C));
	const key key::subtract				((pimpl_t<key>)(0x6D));
	const key key::decimal				((pimpl_t<key>)(0x6E));
	const key key::divide				((pimpl_t<key>)(0x6F));

	const key key::f1					((pimpl_t<key>)(0x70));
	const key key::f2					((pimpl_t<key>)(0x71));
	const key key::f3					((pimpl_t<key>)(0x72));
	const key key::f4					((pimpl_t<key>)(0x73));
	const key key::f5					((pimpl_t<key>)(0x74));
	const key key::f6					((pimpl_t<key>)(0x75));
	const key key::f7					((pimpl_t<key>)(0x76));
	const key key::f8					((pimpl_t<key>)(0x77));
	const key key::f9					((pimpl_t<key>)(0x78));
	const key key::f10					((pimpl_t<key>)(0x79));
	const key key::f11					((pimpl_t<key>)(0x7A));
	const key key::f12					((pimpl_t<key>)(0x7B));
	const key key::f13					((pimpl_t<key>)(0x7C));
	const key key::f14					((pimpl_t<key>)(0x7D));
	const key key::f15					((pimpl_t<key>)(0x7E));
	const key key::f16					((pimpl_t<key>)(0x7F));
	const key key::f17					((pimpl_t<key>)(0x80));
	const key key::f18					((pimpl_t<key>)(0x81));
	const key key::f19					((pimpl_t<key>)(0x82));
	const key key::f20					((pimpl_t<key>)(0x83));
	const key key::f21					((pimpl_t<key>)(0x84));
	const key key::f22					((pimpl_t<key>)(0x85));
	const key key::f23					((pimpl_t<key>)(0x86));
	const key key::f24					((pimpl_t<key>)(0x87));

	const key key::number_lock			((pimpl_t<key>)(0x90));
	const key key::scroll_lock			((pimpl_t<key>)(0x91));
	const key key::left_shift			((pimpl_t<key>)(0xA0));
	const key key::right_shift			((pimpl_t<key>)(0xA1));
	const key key::left_control			((pimpl_t<key>)(0xA2));
	const key key::right_control		((pimpl_t<key>)(0xA3));
	const key key::left_alt				((pimpl_t<key>)(0xA4));
	const key key::right_alt			((pimpl_t<key>)(0xA5));

	const key key::plus					((pimpl_t<key>)(0xBB));
	const key key::comma				((pimpl_t<key>)(0xBC));
	const key key::minus				((pimpl_t<key>)(0xBD));
	const key key::period				((pimpl_t<key>)(0xBE));
	const key key::slash				((pimpl_t<key>)(0xBF));
	const key key::tilde				((pimpl_t<key>)(0xC0));
	const key key::open_square_bracket	((pimpl_t<key>)(0xDB));
	const key key::back_slash			((pimpl_t<key>)(0xDC));
	const key key::close_square_bracket	((pimpl_t<key>)(0xDD));
	const key key::quote				((pimpl_t<key>)(0xDE));
}

#endif