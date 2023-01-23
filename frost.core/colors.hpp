#pragma once
namespace frost {
	struct rgba8;
	struct rgb10a2;
	struct rgba32;

	struct rgba8 final
	{
		using f32	= float;
		using u32	= unsigned long;
		using u8	= unsigned char;

		// Constructors

		rgba8();
		rgba8(u32 code);
		rgba8(u8 r, u8 g, u8 b, u8 a = 255);

		// Casting

		static rgba8 fromRgba(const f32* rgba);
		static rgba8 fromHsva(const f32* hsva);
		static rgba8 fromHsla(const f32* hsla);
		static rgba8 fromCmyk(const f32* cmyk);

		void toRgba(f32* rgba) const;
		void toHsva(f32* hsva) const;
		void toHsla(f32* hsla) const;
		void toCmyk(f32* cmyk) const;

		operator rgb10a2() const;
		operator rgba32() const;

		u8 r;
		u8 g;
		u8 b;
		u8 a;
	};



	struct rgb10a2 final 
	{
		using f32	= float;
		using u32	= unsigned long;
		using u8	= unsigned char;

		// Constructors

		rgb10a2();
		rgb10a2(u32 code);
		rgb10a2(u32 r, u32 g, u32 b, u32 a = 3);

		// Casting

		static rgb10a2 fromRgba(const f32* rgba);
		static rgb10a2 fromHsva(const f32* hsva);
		static rgb10a2 fromHsla(const f32* hsla);
		static rgb10a2 fromCmyk(const f32* cmyk);

		void toRgba(f32* rgba) const;
		void toHsva(f32* hsva) const;
		void toHsla(f32* hsla) const;
		void toCmyk(f32* cmyk) const;

		operator rgba8() const;
		operator rgba32() const;

		u32 r : 10;
		u32 g : 10;
		u32 b : 10;
		u32 a : 2;
	};



	struct rgba32 final 
	{
		using f32	= float;
		using u32	= unsigned long;
		using u8	= unsigned char;

		// Constructors

		rgba32();
		rgba32(u32 code);
		rgba32(f32 r, f32 g, f32 b, f32 a = 1.0f);

		// Casting

		static rgba32 fromRgba(const f32* rgba);
		static rgba32 fromHsva(const f32* hsva);
		static rgba32 fromHsla(const f32* hsla);
		static rgba32 fromCmyk(const f32* cmyk);

		void toRgba(f32* rgba) const;
		void toHsva(f32* hsva) const;
		void toHsla(f32* hsla) const;
		void toCmyk(f32* cmyk) const;

		operator rgba8() const;
		operator rgb10a2() const;

		f32 r = 0.0f;
		f32 g = 0.0f;
		f32 b = 0.0f;
		f32 a = 0.0f;
	};
}