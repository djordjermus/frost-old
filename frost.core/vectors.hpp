#pragma once
namespace frost {
	template<class T> struct vector2;
	template<class T> struct vector3;
	template<class T> struct vector4;
	template<class T> struct matrix4x4;

	template<class T>
	struct vector2 final
	{

		// Constructors

		inline vector2() :
			v{ T(), T() } {}
		inline vector2(T x, T y = T()) :
			v{ x, y } {}

		// Casting

		template<class U>
		inline vector2<U> as2D() const 
		{
			return vector2<U>((U)x, (U)y);
		}
		template<class U>
		inline vector3<U> as3D() const 
		{
			return vector3<U>((U)x, (U)y, U()); 
		}
		template<class U>
		inline vector4<U> as4D() const 
		{
			return vector4<U>((U)x, (U)y, U(), U());
		}
		template<class U>
		inline vector2<U> as() const 
		{
			return as2D<U>(); 
		}

		template<class U>
		inline operator vector2<U>() const 
		{
			return as2D<U>(); 
		}
		template<class U>
		inline operator vector3<U>() const 
		{
			return as3D<U>(); 
		}
		template<class U>
		inline operator vector4<U>() const 
		{
			return as4D<U>(); 
		}

		// Comparison operators

		template<class U>
		inline bool operator==(const vector2<U>& rhs) const 
		{
			return x == rhs.x && y == rhs.y;
		}
		template<class U>
		inline bool operator==(const vector3<U>& rhs) const 
		{
			return x == rhs.x && y == rhs.y && rhs.z == U();
		}
		template<class U>
		inline bool operator==(const vector4<U>& rhs) const 
		{
			return x == rhs.x && y == rhs.y && rhs.z == U() && rhs.w == U();
		}

		template<class U>
		inline bool operator!=(const vector2<U>& rhs) const 
		{
			return x != rhs.x || y != rhs.y;
		}
		template<class U>
		inline bool operator!=(const vector3<U>& rhs) const 
		{
			return x != rhs.x || y != rhs.y || rhs.z != U();
		}
		template<class U>
		inline bool operator!=(const vector4<U>& rhs) const
		{
			return x != rhs.x || y != rhs.y || rhs.z != U() || rhs.w != U();
		}

		// Assignment operators

		template<class U>
		inline void operator+=(const U& rhs) 
		{
			*this = *this + rhs;
		}
		template<class U>
		inline void operator-=(const U& rhs) 
		{
			*this = *this - rhs;
		}
		template<class U>
		inline void operator*=(const U& rhs) 
		{
			*this = *this * rhs;
		}
		template<class U>
		inline void operator/=(const U& rhs) 
		{
			*this = *this / rhs;
		}
		template<class U>
		inline void operator%=(const U& rhs) 
		{
			*this = *this % rhs;
		}
		template<class U>
		inline void operator&=(const U& rhs) 
		{
			*this = *this & rhs;
		}
		template<class U>
		inline void operator|=(const U& rhs) 
		{
			*this = *this | rhs;
		}
		template<class U>
		inline void operator^=(const U& rhs)
		{
			*this = *this ^ rhs;
		}

		// Foreach

		inline T* begin() 
		{ 
			return v;
		}
		inline T* end() 
		{ 
			return v + 2; 
		}
		inline const T* begin() const 
		{ 
			return v;
		}
		inline const T* end() const 
		{ 
			return v + 2;
		}

		// Data

		union {
			struct 
			{
				T x, y; 
			};
			T v[2];
		};
	};

	template<class T> 
	struct vector3 final
	{
		
		// Constructors

		inline vector3() :
			v{ T(), T(), T() } {}
		inline vector3(T x, T y = T(), T z = T()) :
			v{ x, y, z } {}

		// Casting

		template<class U>
		inline vector2<U> as2D() const 
		{ 
			return vector2<U>((U)x, (U)y); 
		}
		template<class U>
		inline vector3<U> as3D() const 
		{
			return vector3<U>((U)x, (U)y, (U)z); 
		}
		template<class U>
		inline vector4<U> as4D() const 
		{
			return vector4<U>((U)x, (U)y, (U)z, U()); 
		}
		template<class U>
		inline vector3<U> as() const 
		{
			return as3D<U>();
		}

		template<class U>
		inline operator vector2<U>() const 
		{ 
			return as2D<U>(); 
		}
		template<class U>
		inline operator vector3<U>() const 
		{ 
			return as3D<U>(); 
		}
		template<class U>
		inline operator vector4<U>() const 
		{ 
			return as4D<U>(); 
		}

		// Comparison operators

		template<class U>
		inline bool operator==(const vector2<U>& rhs) const 
		{
			return x == rhs.x && y == rhs.y && z == U();
		}
		template<class U>
		inline bool operator==(const vector3<U>& rhs) const 
		{
			return x == rhs.x && y == rhs.y && z == rhs.z;
		}
		template<class U>
		inline bool operator==(const vector4<U>& rhs) const 
		{
			return x == rhs.x && y == rhs.y && z == rhs.z && rhs.w == U();
		}

		template<class U>
		inline bool operator!=(const vector2<U>& rhs) const
		{
			return x != rhs.x || y != rhs.y;
		}
		template<class U>
		inline bool operator!=(const vector3<U>& rhs) const 
		{
			return x != rhs.x || y != rhs.y || z != rhs.z;
		}
		template<class U>
		inline bool operator!=(const vector4<U>& rhs) const 
		{
			return x != rhs.x || y != rhs.y || z != rhs.z || rhs.w != U();
		}

		// Assignment operators

		template<class U>
		inline void operator+=(const U& rhs) 
		{
			*this = *this + rhs;
		}
		template<class U>
		inline void operator-=(const U& rhs) 
		{
			*this = *this - rhs;
		}
		template<class U>
		inline void operator*=(const U& rhs)
		{
			*this = *this * rhs;
		}
		template<class U>
		inline void operator/=(const U& rhs) 
		{
			*this = *this / rhs;
		}
		template<class U>
		inline void operator%=(const U& rhs)
		{
			*this = *this % rhs;
		}
		template<class U>
		inline void operator&=(const U& rhs)
		{
			*this = *this & rhs;
		}
		template<class U>
		inline void operator|=(const U& rhs)
		{
			*this = *this | rhs;
		}
		template<class U>
		inline void operator^=(const U& rhs)
		{
			*this = *this ^ rhs;
		}

		// Foreach

		inline T* begin() 
		{ 
			return v;
		}
		inline T* end() 
		{ 
			return v + 3;
		}
		inline const T* begin() const 
		{ 
			return v;
		}
		inline const T* end() const 
		{ 
			return v + 3;
		}

		// Data

		union {
			struct 
			{ 
				T x, y, z;
			};
			T v[3];
		};
	};

	template<class T> 
	struct vector4 final
	{
		
		// Constructors

		inline vector4() :
			v{ T(), T(), T(), T() } {}
		inline vector4(T x, T y = T(), T z = T(), T w = T()) :
			v{ x, y, z, w } {}

		// Casting

		template<class U>
		inline vector2<U> as2D() const 
		{ 
			return vector2<U>((U)x, (U)y);
		}
		template<class U>
		inline vector3<U> as3D() const 
		{ 
			return vector3<U>((U)x, (U)y, (U)z);
		}
		template<class U>
		inline vector4<U> as4D() const 
		{ 
			return vector4<U>((U)x, (U)y, (U)z, (U)w);
		}
		template<class U>
		inline vector4<U> as() const { return as4D<U>(); }

		template<class U>
		inline operator vector2<U>() const 
		{
			return as2D<U>(); 
		}
		template<class U>
		inline operator vector3<U>() const 
		{
			return as3D<U>(); 
		}
		template<class U>
		inline operator vector4<U>() const
		{
			return as4D<U>();
		}

		// Comparison operators

		template<class U>
		inline bool operator==(const vector2<U>& rhs) const 
		{
			return x == rhs.x && y == rhs.y && z == U() && w == U();
		}
		template<class U>
		inline bool operator==(const vector3<U>& rhs) const 
		{
			return x == rhs.x && y == rhs.y && z == rhs.z && w == U();
		}
		template<class U>
		inline bool operator==(const vector4<U>& rhs) const 
		{
			return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w;
		}

		template<class U>
		inline bool operator!=(const vector2<U>& rhs) const
		{
			return x != rhs.x || y != rhs.y || z != U() || w != U();
		}
		template<class U>
		inline bool operator!=(const vector3<U>& rhs) const 
		{
			return x != rhs.x || y != rhs.y || z != rhs.z || w != U();
		}
		template<class U>
		inline bool operator!=(const vector4<U>& rhs) const 
		{
			return x != rhs.x || y != rhs.y || z != rhs.z || w != rhs.w;
		}

		// Assignment operators

		template<class U>
		inline void operator+=(const U& rhs) 
		{
			*this = *this + rhs;
		}
		template<class U>
		inline void operator-=(const U& rhs) 
		{
			*this = *this - rhs;
		}
		template<class U>
		inline void operator*=(const U& rhs) 
		{
			*this = *this * rhs;
		}
		template<class U>
		inline void operator/=(const U& rhs) 
		{
			*this = *this / rhs;
		}
		template<class U>
		inline void operator%=(const U& rhs) 
		{
			*this = *this % rhs;
		}
		template<class U>
		inline void operator&=(const U& rhs) 
		{
			*this = *this & rhs;
		}
		template<class U>
		inline void operator|=(const U& rhs)
		{
			*this = *this | rhs;
		}
		template<class U>
		inline void operator^=(const U& rhs)
		{
			*this = *this ^ rhs;
		}

		// Foreach

		inline T* begin()
		{
			return v;
		}
		inline T* end()
		{
			return v + 4;
		}
		inline const T* begin() const
		{
			return v; }
		inline const T* end() const
		{
			return v + 4;
		}

		// Data

		union {
			struct 
			{ 
				T x, y, z, w; 
			};
			T v[4];
		};
	};
	template<class T>
	struct matrix4x4 {
		using row_t = vector4<T>;

		// Constructors

		inline matrix4x4() :
			m{} {}
		inline matrix4x4(
			const row_t& m1,
			const row_t& m2,
			const row_t& m3,
			const row_t& m4) :
			rows{ m1, m2, m3, m4 } {}
		inline matrix4x4(
			T m11, T m12, T m13, T m14,
			T m21, T m22, T m23, T m24,
			T m31, T m32, T m33, T m34,
			T m41, T m42, T m43, T m44) :
			m
			{ 
				{ m11, m12, m13, m14 },
				{ m21, m22, m23, m24 },
				{ m31, m32, m33, m34 },
				{ m41, m42, m43, m44 }
			} {}

		// Casting

		template<class U>
		inline matrix4x4<U> as() const 
		{ 
			return matrix4x4<U>(
				(U)m11, (U)m12, (U)m13, (U)m14,
				(U)m21, (U)m22, (U)m23, (U)m24,
				(U)m31, (U)m32, (U)m33, (U)m34,
				(U)m41, (U)m42, (U)m43, (U)m44);
		}
		template<class U>
		inline operator matrix4x4<U>() const 
		{
			return as<U>();
		}

		// Comparison operators

		template<class U>
		inline bool operator==(const matrix4x4<U>& rhs) 
		{
			return 
				rows[0] == rhs.rows[0] && 
				rows[1] == rhs.rows[1] && 
				rows[2] == rhs.rows[2] && 
				rows[3] == rhs.rows[3];
		}
		template<class U>
		inline bool operator!=(const matrix4x4<U>& rhs) 
		{
			return
				rows[0] != rhs.rows[0] ||
				rows[1] != rhs.rows[1] ||
				rows[2] != rhs.rows[2] ||
				rows[3] != rhs.rows[3];
		}
		
		// Assignment operators

		template<class U>
		inline void operator+=(const U& rhs)
		{
			*this = *this + rhs;
		}
		template<class U>
		inline void operator-=(const U& rhs)
		{
			*this = *this - rhs;
		}
		template<class U>
		inline void operator*=(const U& rhs)
		{
			*this = *this * rhs;
		}
		template<class U>
		inline void operator/=(const U& rhs)
		{
			*this = *this / rhs;
		}
		template<class U>
		inline void operator%=(const U& rhs)
		{
			*this = *this % rhs;
		}
		template<class U>
		inline void operator&=(const U& rhs)
		{
			*this = *this & rhs;
		}
		template<class U>
		inline void operator|=(const U& rhs)
		{
			*this = *this | rhs;
		}
		template<class U>
		inline void operator^=(const U& rhs)
		{
			*this = *this ^ rhs;
		}

		template<class U>
		auto dot(const matrix4x4<U>& rhs)
		{
			return matrix4x4 {
				rows[0] * rhs.rows[0],
				rows[1] * rhs.rows[1],
				rows[2] * rhs.rows[2],
				rows[3] * rhs.rows[3]};
		}

		// Foreach

		inline row_t* begin() 
		{
			return rows; 
		}
		inline row_t* end() 
		{
			return rows + 4; 
		}
		inline const row_t* begin() const 
		{
			return *rows; 
		}
		inline const row_t* end() const 
		{
			return *rows + 4; 
		}

		// Data

		union {
			struct 
			{
				T
					m11, m12, m13, m14,
					m21, m22, m23, m24,
					m31, m32, m33, m34,
					m41, m42, m43, m44;
			};
			row_t	rows[4];
			T		m[4][4];
		};
	};

	// Unary sign operators

	template<class T>
	inline auto operator+(const vector2<T>& v) 
	{
		return v; 
	}
	template<class T>
	inline auto operator-(const vector2<T>& v) 
	{
		return vector4{ -v.x, -v.y }; 
	}
	template<class T>
	inline auto operator+(const vector3<T>& v) 
	{
		return v; 
	}
	template<class T>
	inline auto operator-(const vector3<T>& v) 
	{
		return vector4{ -v.x, -v.y, -v.z };
	}
	template<class T>
	inline auto operator+(const vector4<T>& v) 
	{
		return v;
	}
	template<class T>
	inline auto operator-(const vector4<T>& v) 
	{
		return vector4{ -v.x, -v.y, -v.z, -v.w };
	}

	// Scalar operators

	template<class T, class U>
	inline auto operator*(const vector2<T>& lhs, const U& rhs) 
	{
		return vector2{ lhs.x * rhs, lhs.y * rhs };
	}
	template<class T, class U>
	inline auto operator/(const vector2<T>& lhs, const U& rhs) 
	{
		return vector2{ lhs.x / rhs, lhs.y / rhs };
	}

	template<class T, class U>
	inline auto operator*(const vector3<T>& lhs, const U& rhs) 
	{
		return vector3{ lhs.x * rhs, lhs.y * rhs, lhs.z * rhs };
	}
	template<class T, class U>
	inline auto operator/(const vector3<T>& lhs, const U& rhs) 
	{
		return vector3{ lhs.x / rhs, lhs.y / rhs, lhs.z / rhs };
	}

	template<class T, class U>
	inline auto operator*(const vector4<T>& lhs, const U& rhs) 
	{
		return vector4{ lhs.x * rhs, lhs.y * rhs, lhs.z * rhs, lhs.w * rhs };
	}
	template<class T, class U>
	inline auto operator/(const vector4<T>& lhs, const U& rhs) 
	{
		return vector4{ lhs.x / rhs, lhs.y / rhs, lhs.z / rhs, lhs.w / rhs };
	}

	template<class T, class U>
	inline auto operator*(const matrix4x4<T>& lhs, const U& rhs) {
		return matrix4x4{ lhs.rows[0] * rhs, lhs.rows[1] * rhs, lhs.rows[2] * rhs, lhs.rows[3] * rhs};
	}
	template<class T, class U>
	inline auto operator/(const matrix4x4<T>& lhs, const U& rhs) {
		return matrix4x4{ lhs.rows[0] / rhs, lhs.rows[1] / rhs, lhs.rows[2] / rhs, lhs.rows[3] / rhs };
	}

	//
	// Vector operators

	template<class T, class U>
	inline auto operator+(const vector2<T>& lhs, const vector2<U>& rhs) 
	{
		return vector4{ lhs.x + rhs.x, lhs.y + rhs.y };
	}
	template<class T, class U>
	inline auto operator-(const vector2<T>& lhs, const vector2<U>& rhs) 
	{
		return vector4{ lhs.x - rhs.x, lhs.y - rhs.y };
	}
	template<class T, class U>
	inline auto operator*(const vector2<T>& lhs, const vector2<U>& rhs) 
	{
		return vector4{ lhs.x * rhs.x, lhs.y * rhs.y };
	}
	template<class T, class U>
	inline auto operator/(const vector2<T>& lhs, const vector2<U>& rhs) 
	{
		return vector4{ lhs.x / rhs.x, lhs.y / rhs.y };
	}

	template<class T, class U>
	inline auto operator+(const vector3<T>& lhs, const vector3<U>& rhs) 
	{
		return vector4{ lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z };
	}
	template<class T, class U>
	inline auto operator-(const vector3<T>& lhs, const vector3<U>& rhs) 
	{
		return vector4{ lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z };
	}
	template<class T, class U>
	inline auto operator*(const vector3<T>& lhs, const vector3<U>& rhs) 
	{
		return vector4{ lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z };
	}
	template<class T, class U>
	inline auto operator/(const vector3<T>& lhs, const vector3<U>& rhs) 
	{
		return vector4{ lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z };
	}
	
	template<class T, class U>
	inline auto operator+(const vector4<T>& lhs, const vector4<U>& rhs)
	{
		return vector4{ lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w };
	}
	template<class T, class U>
	inline auto operator-(const vector4<T>& lhs, const vector4<U>& rhs) 
	{
		return vector4{ lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w };
	}
	template<class T, class U>
	inline auto operator*(const vector4<T>& lhs, const vector4<U>& rhs) 
	{
		return vector4{ lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z, lhs.w * rhs.w };
	}
	template<class T, class U>
	inline auto operator/(const vector4<T>& lhs, const vector4<U>& rhs) 
	{
		return vector4{ lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z, lhs.w / rhs.w };
	}

		template<class T, class U>
	inline auto operator*(const matrix4x4<T>& lhs, const vector4<U>& rhs)
	{
		vector4<decltype(T()* U())> ret;

		T x = lhs.m11;
		T y = lhs.m12;
		T z = lhs.m13;
		T w = lhs.m14;
		ret.x = x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w;

		x = lhs.m21;
		y = lhs.m22;
		z = lhs.m23;
		w = lhs.m24;
		ret.y = x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w;

		x = lhs.m31;
		y = lhs.m32;
		z = lhs.m33;
		w = lhs.m34;
		ret.z = x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w;

		x = lhs.m41;
		y = lhs.m42;
		z = lhs.m43;
		w = lhs.m44;
		ret.w = x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w;

		return ret;
	}
	template<class T, class U>
	inline auto operator*(const vector4<T>& lhs, const matrix4x4<U>& rhs)
	{
		vector4<decltype(T()* U())> ret;

		T x = rhs.m11;
		T y = rhs.m21;
		T z = rhs.m31;
		T w = rhs.m41;
		ret.x = x * lhs.x + y * lhs.y + z * lhs.z + w * lhs.w;

		x = rhs.m12;
		y = rhs.m22;
		z = rhs.m32;
		w = rhs.m42;
		ret.y = x * lhs.x + y * lhs.y + z * lhs.z + w * lhs.w;

		x = rhs.m13;
		y = rhs.m23;
		z = rhs.m33;
		w = rhs.m43;
		ret.z = x * lhs.x + y * lhs.y + z * lhs.z + w * lhs.w;

		x = rhs.m14;
		y = rhs.m24;
		z = rhs.m34;
		w = rhs.m44;
		ret.w = x * lhs.x + y * lhs.y + z * lhs.z + w * lhs.w;

		return ret;
	}

	//
	// Matrix operators

	template<class T, class U>
	inline auto operator*(const matrix4x4<T>& lhs, const matrix4x4<U>& rhs)
	{
		matrix4x4<decltype(T()* U())> ret;

		T x = lhs.m11;
		T y = lhs.m12;
		T z = lhs.m13;
		T w = lhs.m14;
		ret.m11 = x * rhs.m11 + y * rhs.m21 + z * rhs.m31 + w * rhs.m41;
		ret.m12 = x * rhs.m12 + y * rhs.m22 + z * rhs.m32 + w * rhs.m42;
		ret.m13 = x * rhs.m13 + y * rhs.m23 + z * rhs.m33 + w * rhs.m43;
		ret.m14 = x * rhs.m14 + y * rhs.m24 + z * rhs.m34 + w * rhs.m44;

		x = lhs.m21;
		y = lhs.m22;
		z = lhs.m23;
		w = lhs.m24;
		ret.m21 = x * rhs.m11 + y * rhs.m21 + z * rhs.m31 + w * rhs.m41;
		ret.m22 = x * rhs.m12 + y * rhs.m22 + z * rhs.m32 + w * rhs.m42;
		ret.m23 = x * rhs.m13 + y * rhs.m23 + z * rhs.m33 + w * rhs.m43;
		ret.m24 = x * rhs.m14 + y * rhs.m24 + z * rhs.m34 + w * rhs.m44;

		x = lhs.m31;
		y = lhs.m32;
		z = lhs.m33;
		w = lhs.m34;
		ret.m31 = x * rhs.m11 + y * rhs.m21 + z * rhs.m31 + w * rhs.m41;
		ret.m32 = x * rhs.m12 + y * rhs.m22 + z * rhs.m32 + w * rhs.m42;
		ret.m33 = x * rhs.m13 + y * rhs.m23 + z * rhs.m33 + w * rhs.m43;
		ret.m34 = x * rhs.m14 + y * rhs.m24 + z * rhs.m34 + w * rhs.m44;

		x = lhs.m41;
		y = lhs.m42;
		z = lhs.m43;
		w = lhs.m44;
		ret.m41 = x * rhs.m11 + y * rhs.m21 + z * rhs.m31 + w * rhs.m41;
		ret.m42 = x * rhs.m12 + y * rhs.m22 + z * rhs.m32 + w * rhs.m42;
		ret.m43 = x * rhs.m13 + y * rhs.m23 + z * rhs.m33 + w * rhs.m43;
		ret.m44 = x * rhs.m14 + y * rhs.m24 + z * rhs.m34 + w * rhs.m44;

		return ret;
	}

	// Type aliases

	using mf64	= matrix4x4<double>;
	using v4f64	= vector4<double>;
	using v3f64	= vector3<double>;
	using v2f64	= vector2<double>;

	using mf32	= matrix4x4<float>;
	using v4f32	= vector4<float>;
	using v3f32	= vector3<float>;
	using v2f32	= vector2<float>;

	using mu64	= matrix4x4<unsigned long long>;
	using v4u64	= vector4<unsigned long long>;
	using v3u64	= vector3<unsigned long long>;
	using v2u64	= vector2<unsigned long long>;

	using mi64	= matrix4x4<signed long long>;
	using v4i64	= vector4<signed long long>;
	using v3i64	= vector3<signed long long>;
	using v2i64	= vector2<signed long long>;

	using mu32	= matrix4x4<unsigned long>;
	using v4u32	= vector4<unsigned long>;
	using v3u32	= vector3<unsigned long>;
	using v2u32	= vector2<unsigned long>;

	using mi32	= matrix4x4<signed long>;
	using v4i32	= vector4<signed long>;
	using v3i32	= vector3<signed long>;
	using v2i32	= vector2<signed long>;

	using mu16	= matrix4x4<unsigned short>;
	using v4u16	= vector4<unsigned short>;
	using v3u16	= vector3<unsigned short>;
	using v2u16	= vector2<unsigned short>;

	using mi16	= matrix4x4<signed short>;
	using v4i16	= vector4<signed short>;
	using v3i16	= vector3<signed short>;
	using v2i16	= vector2<signed short>;

	using mu8	= matrix4x4<unsigned char>;
	using v4u8	= vector4<unsigned char>;
	using v3u8	= vector3<unsigned char>;
	using v2u8	= vector2<unsigned char>;

	using mi8	= matrix4x4<unsigned char>;
	using v4i8	= vector4<unsigned char>;
	using v3i8	= vector3<unsigned char>;
	using v2i8	= vector2<unsigned char>;
}