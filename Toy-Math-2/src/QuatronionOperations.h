#pragma once

#include "Quatronions.h"
#include <cmath>

namespace Toy::Math
{
	template<class T>
	constexpr inline Quatronion<T> operator+(const Quatronion<T>& left, const Quatronion<T>& right)
	{
		return { left.s + right.s,left.v + right.v };
	}
	template<class T>
	constexpr inline Quatronion<T> operator-(const Quatronion<T>& left, const Quatronion<T>& right)
	{
		return { left.s - right.s,left.v - right.v };
	}
	template<class T>
	constexpr inline Quatronion<T> operator*(const Quatronion<T>& left, const Quatronion<T>& right)
	{
		return	{	
					left.s * right.s - left.x * right.x - left.y * right.y - left.z * right.z,
					left.s * right.x + left.x * right.s + left.y * right.z - left.z * right.y,
					left.s * right.y - left.x * right.z + left.y * right.s + left.z * right.x,
					left.s * right.z + left.x * right.y - left.y * right.x + left.z * right.s
				};
	}
	template<class T>
	constexpr inline Quatronion<T> operator*(const Quatronion<T>& left, const T& right)
	{
		return { left.s * right,left.v * right };
	}
	template<class T>
	constexpr inline Quatronion<T> operator/(const Quatronion<T>& left, const T& right)
	{
		return { left.s / right,left.v / right };
	}

	template<class T>
	constexpr inline float Lenght(const Quatronion<T>& q)
	{
		return std::sqrtf(q.s * q.s + q.x * q.x + q.y * q.y + q.z * q.z);
	}
	template<class T>
	constexpr inline double Lenghtd(const Quatronion<T>& q)
	{
		return std::sqrt(q.s * q.s + q.x * q.x + q.y * q.y + q.z * q.z);
	}
	template<class T>
	constexpr inline T LenghtSq(const Quatronion<T>& q)
	{
		return q.s * q.s + q.x * q.x + q.y * q.y + q.z * q.z;
	}

	template<class T>
	constexpr inline Quatronion<float> Normalize(const Quatronion<T>& q)
	{
		float l = Lenght(q);
		return { q.s / l,q.x / l,q.y / l,q.z / l };
	}
	constexpr inline Quatronion<double> Normalize(const Quatronion<double>& q)
	{
		double l = Lenghtd(q);
		return { q.s / l,q.x / l,q.y / l,q.z / l };
	}

	template<class T>
	constexpr inline Quatronion<T> Conjugate(const Quatronion<T>& q)
	{
		return { q.s,-q.v };
	}
	template<class T>
	constexpr inline Quatronion<T> Inverse(const Quatronion<T>& q)
	{
		return Conjugate(q) / LenghtSq(q);
	}
}