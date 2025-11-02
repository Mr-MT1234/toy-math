#pragma once

#include "Vectors.h"
#include <cmath>

namespace Toy::Math
{
#pragma region General operators

	template<class T,size_t... Ns>
	constexpr inline Vec<T, Seq<Ns...>> operator+(const Vec<T, Seq<Ns...>>& left, const Vec<T, Seq<Ns...>>& right)
	{
		return { (left[Ns] + right[Ns])... };
	}

	template<class T>
	constexpr inline Vector4<T> operator+(const Vector4<T>& left, const Vector4<T>& right)
	{
		return { left.x + right.x,left.y + right.y ,left.z + right.z ,left.w + right.w };
	}
	template<class T, size_t... Ns>
	constexpr inline Vec<T, Seq<Ns...>> operator+(const Vec<T, Seq<Ns...>>& left, T right)
	{
		return { (left[Ns] + right)... };
	}
	template<class T, size_t... Ns>
	constexpr inline Vec<T, Seq<Ns...>> operator+(T left, const Vec<T, Seq<Ns...>>& right)
	{
		return { (left + right[Ns])... };
	}

	template<class T, size_t... Ns>
	constexpr inline Vec<T, Seq<Ns...>> operator-(const Vec<T, Seq<Ns...>>& left, const Vec<T, Seq<Ns...>>& right)
	{
		return { (left[Ns] - right[Ns])... };
	}
	template<class T, size_t... Ns>
	constexpr inline Vec<T, Seq<Ns...>> operator-(const Vec<T, Seq<Ns...>>& left, T right)
	{
		return { (left[Ns] - right)... };
	}
	template<class T, size_t... Ns>
	constexpr inline Vec<T, Seq<Ns...>> operator-(T left, const Vec<T, Seq<Ns...>>& right)
	{
		return { (left - right[Ns])... };
	}
	template<class T, size_t... Ns>
	constexpr inline Vec<T, Seq<Ns...>> operator-(const Vec<T, Seq<Ns...>>& v)
	{
		return { (-v[Ns])... };
	}

	template<class T, size_t... Ns>
	constexpr inline Vec<T, Seq<Ns...>> operator*(const Vec<T, Seq<Ns...>>& left, const Vec<T, Seq<Ns...>>& right)
	{
		return { (left[Ns] * right[Ns])... };
	}
	template<class T, size_t... Ns>
	constexpr inline Vec<T, Seq<Ns...>> operator*(const Vec<T, Seq<Ns...>>& left, T right)
	{
		return { (left[Ns] * right)... };
	}
	template<class T, size_t... Ns>
	constexpr inline Vec<T, Seq<Ns...>> operator*(T left, const Vec<T, Seq<Ns...>>& right)
	{
		return { (left * right[Ns])... };
	}

	template<class T, size_t... Ns>
	constexpr inline Vec<T, Seq<Ns...>> operator/(const Vec<T, Seq<Ns...>>& left, const Vec<T, Seq<Ns...>>& right)
	{
		TOY_MATH_ASSERT(((right[Ns] != 0) && ...), "Zero division");
		return { (left[Ns] / right[Ns])... };
	}
	template<class T, size_t... Ns>
	constexpr inline Vec<T, Seq<Ns...>> operator/(const Vec<T, Seq<Ns...>>& left, T right)
	{
		TOY_MATH_ASSERT(right != 0 , "Zero division");
		return { (left[Ns] / right)... };
	}
	template<class T, size_t... Ns>
	constexpr inline Vec<T, Seq<Ns...>> operator/(T left, const Vec<T, Seq<Ns...>>& right)
	{
		TOY_MATH_ASSERT(((right[Ns] != 0) && ...), "Zero division");
		return { (left / right[Ns])... };
	}

	template<class T, size_t... Ns>
	constexpr inline T Dot(const Vec<T, Seq<Ns...>>& left, const Vec<T, Seq<Ns...>>& right)
	{
		return ( (left[Ns] * right[Ns]) + ... );
	}

	template<class T, size_t... Ns>
	constexpr inline float Lenght(const Vec<T, Seq<Ns...>>& v)
	{
		return std::sqrtf(((v[Ns] * v[Ns]) + ...));
	}
	template<class T, size_t... Ns>
	constexpr inline double Lenghtd(const Vec<T, Seq<Ns...>>& v)
	{
		return std::sqrt(((v[Ns] * v[Ns]) + ...));
	}
	template<class T, size_t... Ns>
	constexpr inline T LenghtSq(const Vec<T, Seq<Ns...>>& v)
	{
		return ((v[Ns] * v[Ns]) + ...);
	}

	template<class T, size_t... Ns>
	constexpr inline Vec<float, Seq<Ns...>> Normalize(const Vec<T, Seq<Ns...>>& v)
	{
		float lenght = Lenght(v);
		return { (v[Ns] / lenght)... };
	}
	template<size_t... Ns>
	constexpr inline Vec<double, Seq<Ns...>> Normalize(const Vec<double, Seq<Ns...>>& v)
	{
		return v / Lenght(v);
	}
#pragma endregion 
//----------------------------------------------------------------------------------------------------------------------------------------------
#pragma region Compound assignment

	template<class T, size_t... Ns>
	constexpr inline Vec<T, Seq<Ns...>>& operator+=(Vec<T, Seq<Ns...>>& left, const Vec<T, Seq<Ns...>>& right)
	{
		((left[Ns] += right[Ns]),...);
		return left;
	}
	template<class T, size_t... Ns>
	constexpr inline Vec<T, Seq<Ns...>>& operator+=(Vec<T, Seq<Ns...>>& left,  T right)
	{
		((left[Ns] += right),...);
		return left;
	}

	template<class T, size_t... Ns>
	constexpr inline Vec<T, Seq<Ns...>>& operator-=(Vec<T, Seq<Ns...>>& left, const Vec<T, Seq<Ns...>>& right)
	{
		((left[Ns] -= right[Ns]), ...);
		return left;
	}
	template<class T, size_t... Ns>
	constexpr inline Vec<T, Seq<Ns...>>& operator-=(Vec<T, Seq<Ns...>>& left, T right)
	{
		((left[Ns] -= right), ...);
		return left;
	}
												 
	template<class T, size_t... Ns>
	constexpr inline Vec<T, Seq<Ns...>>& operator*=(Vec<T, Seq<Ns...>>& left, const Vec<T, Seq<Ns...>>& right)
	{
		((left[Ns] *= right[Ns]), ...);
		return left;
	}
	template<class T, size_t... Ns>
	constexpr inline Vec<T, Seq<Ns...>>& operator*=(Vec<T, Seq<Ns...>>& left, T right)
	{
		((left[Ns] *= right), ...);
		return left;
	}
												 
	template<class T, size_t... Ns>				 
	constexpr inline Vec<T, Seq<Ns...>>& operator/=(Vec<T, Seq<Ns...>>& left, const Vec<T, Seq<Ns...>>& right)
	{											 
		TOY_MATH_ASSERT(((right[Ns] != 0) && ...), "Zero division");
		((left[Ns] /= right[Ns]), ...);
		return left;
	}											 
	template<class T, size_t... Ns>				 
	constexpr inline Vec<T, Seq<Ns...>>& operator/=(Vec<T, Seq<Ns...>>& left, T right)
	{
		TOY_MATH_ASSERT(right != 0, "Zero division");
		((left[Ns] /= right), ...);
		return left;
	}

#pragma endregion
//----------------------------------------------------------------------------------------------------------------------------------------------
#pragma region Logical operators

	template<class T, size_t... Ns>
	constexpr inline typename Vec<T, Seq<Ns...>>::bool_type operator<(const Vec<T, Seq<Ns...>>& left, const Vec<T, Seq<Ns...>>& right)
	{
		return { (left[Ns] < right[Ns])... };
	}
	template<class T, size_t... Ns>
	constexpr inline typename Vec<T, Seq<Ns...>>::bool_type operator>(const Vec<T, Seq<Ns...>>& left, const Vec<T, Seq<Ns...>>& right)
	{
		return { (left[Ns] > right[Ns])... };
	}

	template<class T, size_t... Ns>
	constexpr inline typename Vec<T, Seq<Ns...>>::bool_type operator<=(const Vec<T, Seq<Ns...>>& left, const Vec<T, Seq<Ns...>>& right)
	{
		return { (left[Ns] <= right[Ns])... };
	}
	template<class T, size_t... Ns>
	constexpr inline typename Vec<T, Seq<Ns...>>::bool_type operator>=(const Vec<T, Seq<Ns...>>& left, const Vec<T, Seq<Ns...>>& right)
	{
		return { (left[Ns] >= right[Ns])... };
	}

	template<class T, size_t... Ns>
	constexpr inline bool operator==(const Vec<T, Seq<Ns...>>& left, const Vec<T, Seq<Ns...>>& right)
	{
		return ((left[Ns] == right[Ns]) && ...);
	}
	template<class T, size_t... Ns>
	constexpr inline bool operator!=(const Vec<T, Seq<Ns...>>& left, const Vec<T, Seq<Ns...>>& right)
	{
		return ((left[Ns] != right[Ns]) || ...);
	}

	template<class T, size_t... Ns>
	constexpr inline typename Vec<T, Seq<Ns...>>::bool_type EqualsComp(const Vec<T, Seq<Ns...>>& left, const Vec<T, Seq<Ns...>>& right)
	{
		return { (left[Ns] == right[Ns])... };
	}
	template<class T, size_t... Ns>
	constexpr inline typename Vec<T, Seq<Ns...>>::bool_type NotEqualsComp(const Vec<T, Seq<Ns...>>& left, const Vec<T, Seq<Ns...>>& right)
	{
		return { (left[Ns] != right[Ns])... };
	}

	template<size_t... Ns>
	constexpr inline typename Vec<bool, Seq<Ns...>>::bool_type operator&&(const Vec<bool, Seq<Ns...>>& left, const Vec<bool, Seq<Ns...>>& right)
	{
		return { (left[Ns] && right[Ns])... };
	}
	template<size_t... Ns>
	constexpr inline typename Vec<bool, Seq<Ns...>>::bool_type operator||(const Vec<bool, Seq<Ns...>>& left, const Vec<bool, Seq<Ns...>>& right)
	{
		return { (left[Ns] || right[Ns])... };
	}
	template<size_t... Ns>
	constexpr inline typename Vec<bool, Seq<Ns...>>::bool_type operator!(const Vec<bool, Seq<Ns...>>& v)
	{
		return { !v[Ns]... };
	}

	template<size_t... Ns>
	constexpr inline bool All(const Vec<bool, Seq<Ns...>>& v)
	{
		return (v[Ns] &&...);
	}
	template<size_t... Ns>
	constexpr inline bool Any (const Vec<bool, Seq<Ns...>>& v)
	{
		return (v[Ns] || ...);
	}
#pragma endregion
//--------------------------------------------------------------------------------------------------------------------------------------------------------
#pragma region Handy Functions

	template<class T, size_t... Ns>
	constexpr inline Vec<T, Seq<Ns...>> Min(const Vec<T, Seq<Ns...>>& v1, const Vec<T, Seq<Ns...>>& v2)
	{
		auto min = [](const T& a, const T& b) {return a < b ? a : b; };
		return { (min(v1[Ns],v2[Ns]))... };
	}
	template<class T, size_t... Ns>
	constexpr inline Vec<T, Seq<Ns...>> Max(const Vec<T, Seq<Ns...>>& v1, const Vec<T, Seq<Ns...>>& v2)
	{
		auto max = [](const T& a, const T& b) {return a > b ? a : b; };
		return { (max(v1[Ns],v2[Ns]))... };
	}
	template<class T, size_t... Ns>
	constexpr inline Vec<T, Seq<Ns...>> Abs(const Vec<T, Seq<Ns...>>& v)
	{
		auto abs = [](const T& a) {return a >= 0 ? a : -a; };
		return { (abs(v[Ns]))... };
	}
	template<class T, size_t... Ns>
	constexpr inline Vec<T, Seq<Ns...>>& Clamp(const Vec<T, Seq<Ns...>>& v,const T& min,const T& max)
	{
		auto clamp = [](const T& a,const T& min, const T& max) 
		{
			if (a < min) return min;
			if (a > max) return max;
			return a;
		};
		return { (clamp(v[Ns],min,max))... };
	}
	template<class T, size_t... Ns>
	constexpr inline Vec<T, Seq<Ns...>> Clamp(const Vec<T, Seq<Ns...>>& v, const Vec<T, Seq<Ns...>>& min, const Vec<T, Seq<Ns...>>& max)
	{
		auto clamp = [](const T& a, const T& min, const T& max)
		{
			if (a < min) return min;
			if (a > max) return max;
			return a;
		};
		return { (clamp(v[Ns],min[Ns],max[Ns]))... };
	}
	template<class T, size_t... Ns>
	constexpr inline Vec<T, Seq<Ns...>> Lerp(const Vec<T, Seq<Ns...>>& v1, const Vec<T, Seq<Ns...>>& v2, const float t)
	{
		auto lerp = [](const T& a, const T& b, const float t) -> T
		{
			return b * t + a * (1 - t);
		};
		return { lerp(v1[Ns],v2[Ns],t)... };
	}

#pragma endregion
//-----------------------------------------------------------------------------------------------------------------------------------------------
#pragma region Exeptions

	template<class T>
	constexpr inline T Cross(const Vector2<T>& left, const Vector2<T>& right)
	{
		return left.x * right.y - left.y * right.x;
	}
	template<class T>
	constexpr inline Vector3<T> Cross(const Vector3<T>& left, const Vector3<T>& right)
	{
		return	{
					left.y * right.z - left.z * right.y,
					left.z * right.x - left.x * right.z,
					left.x * right.y - left.y * right.x
				};
	}

#pragma endregion
}