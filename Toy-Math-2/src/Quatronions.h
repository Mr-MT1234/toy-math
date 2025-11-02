#pragma once

#include "Vectors.h"

namespace Toy::Math
{
	template<class T>
	struct Quat
	{
		T s;
		union
		{
			Vector3<T> v;
			struct { T x, y, z; };
		};

		constexpr Quat(const T& s, const T& x, const T& y, const T& z)
			:s(s), v(x, y, z)
		{}
		constexpr Quat(const T& s, const Vector3<T>& v)
			:s(s), v(v)
		{}
	};

	template<class T>
	using Quatronion = Quat<T>;

	typedef Quatronion<float> Quatronionf;
	typedef Quatronion<double> Quatroniond;
}