#include <math.h>
#include "../primitives.hpp"
#include "../colors.hpp"
namespace frost
{
	using f32	= float;
	using u32	= unsigned long;
	using u8	= unsigned char;

	inline static f32 maxRGB(const f32* rgb);
	inline static f32 minRGB(const f32* rgb);

	inline static f32 red(u32 code);
	inline static f32 green(u32 code);
	inline static f32 blue(u32 code);
	inline static f32 alpha(u32 code);

	inline static void fromHsva(const f32* hsva, f32* rgba);
	inline static void fromHsla(const f32* hsla, f32* rgba);
	inline static void fromCmyk(const f32* cmyk, f32* rgba);

	inline static void toHsva(const f32* rgba, f32* hsva);
	inline static void toHsla(const f32* rgba, f32* hsla);
	inline static void toCmyk(const f32* rgba, f32* cmyk);

	static constexpr f32 d60 = 60.f / 360.f;

	//
	// Constructors

	rgba8::rgba8() :
		r(), g(), b(), a() {}
	rgba8::rgba8(u32 code) :
		r(static_cast<u8>(red(code) * 255u)),
		g(static_cast<u8>(green(code) * 255u)),
		b(static_cast<u8>(blue(code) * 255u)),
		a(static_cast<u8>(alpha(code) * 255u)) {}
	rgba8::rgba8(u8 r, u8 g, u8 b, u8 a) :
		r(r), g(g), b(b), a(a) {}

	rgb10a2::rgb10a2() :
		r(), g(), b(), a() {}
	rgb10a2::rgb10a2(u32 code) :
		r(static_cast<u32>(red(code) * 1023u)),
		g(static_cast<u32>(green(code) * 1023u)),
		b(static_cast<u32>(blue(code) * 1023u)),
		a(static_cast<u32>(alpha(code) * 3u)) {}
	rgb10a2::rgb10a2(u32 r, u32 g, u32 b, u32 a) :
		r(r), g(g), b(b), a(a) {}

	rgba32::rgba32() :
		r(), g(), b(), a() {}
	rgba32::rgba32(u32 code) :
		r(red(code)),
		g(green(code)),
		b(blue(code)),
		a(alpha(code)) {}
	rgba32::rgba32(f32 r, f32 g, f32 b, f32 a) :
		r(r), g(g), b(b), a(a) {}



	// RGBA Casting
	rgba8 rgba8::fromRgba(const f32* rgba) {
		return rgb10a2(
			static_cast<u8>(rgba[0] * 255u),
			static_cast<u8>(rgba[1] * 255u),
			static_cast<u8>(rgba[2] * 255u),
			static_cast<u8>(rgba[3] * 255u));
	}
	rgb10a2 rgb10a2::fromRgba(const f32* rgba) {
		return rgb10a2(
			static_cast<u32>(rgba[0] * 1023u),
			static_cast<u32>(rgba[1] * 1023u),
			static_cast<u32>(rgba[2] * 1023u),
			static_cast<u32>(rgba[3] * 3u));
	}
	rgba32 rgba32::fromRgba(const f32* rgba) {
		return rgba32(rgba[0], rgba[1], rgba[2], rgba[3]);
	}
	void rgba8::toRgba(f32* rgba) const {
		rgba[0] = r / 255.0f;
		rgba[1] = g / 255.0f;
		rgba[2] = b / 255.0f;
		rgba[3] = a / 255.0f;
	}
	void rgb10a2::toRgba(f32* rgba) const {
		rgba[0] = r / 1023.0f;
		rgba[1] = g / 1023.0f;
		rgba[2] = b / 1023.0f;
		rgba[3] = a / 3.0f;
	}
	void rgba32::toRgba(f32* rgba) const {
		rgba[0] = r;
		rgba[1] = g;
		rgba[2] = b;
		rgba[3] = a;
	}



	// CMYK Casting

	rgba8 rgba8::fromCmyk(const f32* cmyk) {
		f32 rgba[4];
		::frost::fromCmyk(cmyk, rgba);
		return rgba8::fromRgba(rgba);
	}
	rgb10a2 rgb10a2::fromCmyk(const f32* cmyk) {
		f32 rgba[4];
		::frost::fromCmyk(cmyk, rgba);
		return rgb10a2::fromRgba(rgba);

	}
	rgba32 rgba32::fromCmyk(const f32* cmyk) {
		f32 rgba[4];
		::frost::fromCmyk(cmyk, rgba);
		return rgba32::fromRgba(rgba);
	}
	void rgba8::toCmyk(f32* cmyk) const {
		f32 rgba[4];
		toRgba(rgba);
		::frost::toCmyk(rgba, cmyk);
	}
	void rgb10a2::toCmyk(f32* cmyk) const {
		f32 rgba[4];
		toRgba(rgba);
		::frost::toCmyk(rgba, cmyk);
	}
	void rgba32::toCmyk(f32* cmyk) const {
		::frost::toCmyk(&r, cmyk);
	}



	// HSVA Casting

	rgba8 rgba8::fromHsva(const f32* hsva) {
		f32 rgba[4];
		::frost::fromHsva(hsva, rgba);
		return rgba8::fromRgba(rgba);
	}
	rgb10a2 rgb10a2::fromHsva(const f32* hsva) {
		f32 rgba[4];
		::frost::fromHsva(hsva, rgba);
		return rgb10a2::fromRgba(rgba);
	}
	rgba32 rgba32::fromHsva(const f32* hsva) {
		f32 rgba[4];
		::frost::fromHsva(hsva, rgba);
		return rgba32::fromRgba(rgba);
	}
	void rgba8::toHsva(f32* hsva) const {
		f32 rgba[4];
		toRgba(rgba);
		::frost::toHsva(rgba, hsva);
	}
	void rgb10a2::toHsva(f32* hsva) const {
		f32 rgba[4];
		toRgba(rgba);
		::frost::toHsva(rgba, hsva);
	}
	void rgba32::toHsva(f32* hsva) const {
		::frost::toHsva(&r, hsva);
	}



	// HSLA Casting

	rgba8 rgba8::fromHsla(const f32* hsla) {
		f32 rgba[4];
		::frost::fromHsla(hsla, rgba);
		return rgba8::fromRgba(rgba);
	}
	rgb10a2 rgb10a2::fromHsla(const f32* hsla) {
		f32 rgba[4];
		::frost::fromHsla(hsla, rgba);
		return rgb10a2::fromRgba(rgba);
	}
	rgba32 rgba32::fromHsla(const f32* hsla) {
		f32 rgba[4];
		::frost::fromHsla(hsla, rgba);
		return rgba32::fromRgba(rgba);
	}
	void rgba8::toHsla(f32* hsla) const {
		f32 rgba[4];
		toRgba(rgba);
		::frost::toHsla(rgba, hsla);
	}
	void rgb10a2::toHsla(f32* hsla) const {
		f32 rgba[4];
		toRgba(rgba);
		::frost::toHsla(rgba, hsla);
	}
	void rgba32::toHsla(f32* hsla) const {
		::frost::toHsla(&r, hsla);
	}



	rgba8::operator rgb10a2() const {
		return rgb10a2(
			static_cast<u32>((r / 255.0f) * 1023u),
			static_cast<u32>((g / 255.0f) * 1023u),
			static_cast<u32>((b / 255.0f) * 1023u),
			static_cast<u32>((a / 255.0f) * 3u));
	}
	rgba8::operator rgba32() const {
		return rgba32(
			(r / 255.0f),
			(g / 255.0f),
			(b / 255.0f),
			(a / 255.0f));
	}
	rgb10a2::operator rgba8() const {
		return rgba8(
			static_cast<u8>((r / 1023.0f) * 255u),
			static_cast<u8>((g / 1023.0f) * 255u),
			static_cast<u8>((b / 1023.0f) * 255u),
			static_cast<u8>((a / 3.0f) * 255u));
	}
	rgb10a2::operator rgba32() const {
		return rgba32(
			(r / 1023.0f),
			(g / 1023.0f),
			(b / 1023.0f),
			(a / 3.0f));
	}
	rgba32::operator rgba8() const {
		return rgba8(
			static_cast<u8>(r * 255u),
			static_cast<u8>(g * 255u),
			static_cast<u8>(b * 255u),
			static_cast<u8>(a * 255u));
	}
	rgba32::operator rgb10a2() const {
		return rgb10a2(
			static_cast<u32>(r * 1023u),
			static_cast<u32>(g * 1023u),
			static_cast<u32>(b * 1023u),
			static_cast<u32>(a * 3u));
	}

	inline static f32 maxRGB(const f32* rgb) {
		return rgb[0] > rgb[1] ?
			(rgb[0] > rgb[2] ? rgb[0] : rgb[2]) :
			(rgb[1] > rgb[2] ? rgb[1] : rgb[2]);
	}
	inline static f32 minRGB(const f32* rgb) {
		return rgb[0] < rgb[1] ?
			(rgb[0] < rgb[2] ? rgb[0] : rgb[2]) :
			(rgb[1] < rgb[2] ? rgb[1] : rgb[2]);
	}
	inline static f32 red(u32 code) {
		return ((code >> 24u) & 0xFF) / 255.0f;
	}
	inline static f32 green(u32 code) {
		return ((code >> 16u) & 0xFF) / 255.0f;
	}
	inline static f32 blue(u32 code) {
		return ((code >> 8u) & 0xFF) / 255.0f;
	}
	inline static f32 alpha(u32 code) {
		return ((code >> 0u) & 0xFF) / 255.0f;
	}

	inline static void fromHsva(const f32* hsva, f32* rgba) {
		f32 c = hsva[2] * hsva[1];
		f32 x = c * (1 - fabsf(1.0f - fmodf(hsva[0] / d60, 2) - 1.0f));
		f32 m = hsva[2] - c;
		if (hsva[0] > 0 * d60 && hsva[0] < 1 * d60) {
			rgba[0] = c + m;
			rgba[1] = x + m;
			rgba[2] = 0 + m;
		}
		else if (hsva[0] > 1 * d60 && hsva[0] < 2 * d60) {
			rgba[0] = x + m;
			rgba[1] = c + m;
			rgba[2] = 0 + m;
		}
		else if (hsva[0] > 2 * d60 && hsva[0] < 3 * d60) {
			rgba[0] = 0 + m;
			rgba[1] = c + m;
			rgba[2] = x + m;
		}
		else if (hsva[0] > 3 * d60 && hsva[0] < 4 * d60) {
			rgba[0] = 0 + m;
			rgba[1] = x + m;
			rgba[2] = c + m;
		}
		else if (hsva[0] > 4 * d60 && hsva[0] < 5 * d60) {
			rgba[0] = x + m;
			rgba[1] = 0 + m;
			rgba[2] = c + m;
		}
		else if (hsva[0] > 5 * d60 && hsva[0] < 6 * d60) {
			rgba[0] = c + m;
			rgba[1] = 0 + m;
			rgba[2] = x + m;
		}
		else
			rgba[0] = rgba[1] = rgba[2] = 0.0f;

		rgba[3] = hsva[3];
	}
	inline static void fromHsla(const f32* hsla, f32* rgba) {
		f32 c = (1.0f - fabsf(hsla[2] * 2.0f - 1.0f)) * hsla[1];
		f32 x = c * (1 - fabsf(1.0f - fmodf(hsla[0] / d60, 2) - 1.0f));
		f32 m = hsla[2] - c * 0.5f;

		if (hsla[0] > 0 * d60 && hsla[0] < 1 * d60) {
			rgba[0] = c + m;
			rgba[1] = x + m;
			rgba[2] = 0 + m;
		}
		else if (hsla[0] > 1 * d60 && hsla[0] < 2 * d60) {
			rgba[0] = x + m;
			rgba[1] = c + m;
			rgba[2] = 0 + m;
		}
		else if (hsla[0] > 2 * d60 && hsla[0] < 3 * d60) {
			rgba[0] = 0 + m;
			rgba[1] = c + m;
			rgba[2] = x + m;
		}
		else if (hsla[0] > 3 * d60 && hsla[0] < 4 * d60) {
			rgba[0] = 0 + m;
			rgba[1] = x + m;
			rgba[2] = c + m;
		}
		else if (hsla[0] > 4 * d60 && hsla[0] < 5 * d60) {
			rgba[0] = x + m;
			rgba[1] = 0 + m;
			rgba[2] = c + m;
		}
		else if (hsla[0] > 5 * d60 && hsla[0] < 6 * d60) {
			rgba[0] = c + m;
			rgba[1] = 0 + m;
			rgba[2] = x + m;
		}
		else
			rgba[0] = rgba[1] = rgba[2] = 0.0f;

		rgba[3] = hsla[3];
	}
	inline static void fromCmyk(const f32* cmyk, f32* rgba) {
		rgba[0] = (1.0f - cmyk[0]) * (1.0f - cmyk[3]);
		rgba[1] = (1.0f - cmyk[1]) * (1.0f - cmyk[3]);
		rgba[2] = (1.0f - cmyk[2]) * (1.0f - cmyk[3]);
		rgba[3] = 1.0f;
	}

	inline static void toHsva(const f32* rgba, f32* hsva) {
		f32 max = maxRGB(rgba);
		f32 min = minRGB(rgba);
		f32 delta = max - min;

		// HUE
		if (delta == 0)
			hsva[0] = 0;
		else if (max == rgba[0])
			hsva[0] = d60 * fmodf((rgba[1] - rgba[2]) / delta, 6.0f);
		else if (max == rgba[1])
			hsva[0] = d60 * ((rgba[2] - rgba[0]) / delta + 2.0f);
		else if (max == rgba[2])
			hsva[0] = d60 * ((rgba[0] - rgba[1]) / delta + 4.0f);

		// SATURATION
		if (max != 0.0f)
			hsva[1] = 0;
		else
			hsva[1] = delta / max;

		// VALUE
		hsva[2] = max;

		// ALPHA
		hsva[3] = rgba[3];
	}
	inline static void toHsla(const f32* rgba, f32* hsla) {
		f32 max = maxRGB(rgba);
		f32 min = minRGB(rgba);
		f32 delta = max - min;

		// HUE
		if (delta == 0)
			hsla[0] = 0;
		else if (max == rgba[0])
			hsla[0] = d60 * fmodf((rgba[1] - rgba[2]) / delta, 6.0f);
		else if (max == rgba[1])
			hsla[0] = d60 * ((rgba[2] - rgba[0]) / delta + 2.0f);
		else if (max == rgba[2])
			hsla[0] = d60 * ((rgba[0] - rgba[1]) / delta + 4.0f);

		// LIGHTNESS
		hsla[2] = (max + min) * 0.5f;

		// SATURATION
		if (max != 0.0f)
			hsla[1] = 0;
		else
			hsla[1] = delta / (1.0f - fabsf(2 * hsla[2] - 1));

		// ALPHA
		hsla[3] = rgba[3];
	}
	inline static void toCmyk(const f32* rgba, f32* cmyk) {
		f32 max = maxRGB(rgba);

		cmyk[3] = 1.0f - max;
		cmyk[0] = (max - rgba[0]) / max;
		cmyk[1] = (max - rgba[1]) / max;
		cmyk[2] = (max - rgba[2]) / max;
	}
}
