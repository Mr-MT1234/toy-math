#pragma once
#include <utility>
#include "Defines.h"

namespace Toy::Math
{
	template<size_t... Ns> using Seq = Sequence<Ns...>;
	template<size_t N> using MakeSeq = MakeSequence<N>;
	template<size_t From,size_t To> using MakeSeqFromTo = MakeSequenceFromTo<From,To>;

	template<class T, class Seq> struct Vec;

	template<class T,size_t... Ns>
	struct Vec<T, Seq<Ns...>>
	{
		typedef Vec<bool, Seq<Ns...>> bool_type;

		T elements[sizeof...(Ns)];

		constexpr Vec()
			: elements{0}
		{}
		constexpr Vec(const T& value)
			: elements{ returnBack<Ns>(value)... }
		{}
		constexpr Vec(const alwaysType<T,Ns>&... values)
			: elements{ values... }
		{}

		constexpr inline T& operator[](size_t i)
		{
			TOY_MATH_ASSERT(i < sizeof...(Ns), "Index out of bounds");
			return elements[i];
		}
		constexpr inline const T& operator[](size_t i) const
		{
			TOY_MATH_ASSERT(i < sizeof...(Ns), "Index out of bounds");
			return elements[i];
		}
		constexpr inline T& get(size_t i)
		{
			TOY_MATH_ASSERT(i < sizeof...(Ns), "Index out of bounds");
			return elements[i];
		}
		constexpr inline const T& get(size_t i) const
		{
			TOY_MATH_ASSERT(i < sizeof...(Ns), "Index out of bounds");
			return elements[i];
		}

		constexpr inline size_t size() const
		{
			return sizeof...(Ns);
		}

		template<size_t From, size_t To>
		constexpr inline Vec<T, MakeSeq<To - From>> subVector() const
		{
			static_assert(From < sizeof...(Ns) && To <= sizeof...(Ns) && To > From, "subVector out of bounds");
			return subVectorImpl(MakeSeqFromTo<From, To>());
		}
	private:
		template<size_t... Ns>
		constexpr inline Vec<T, MakeSeq<sizeof...(Ns)>> subVectorImpl(const Seq<Ns...>&) const
		{
			return { get(Ns)... };
		}
		template<size_t N>
		static constexpr inline const T& returnBack(const T& a) { return a; }
	};

	template<class T>
	struct Vec<T, MakeSeq<1>>
	{
		typedef Vec<bool, MakeSeq<1>> bool_type;

		union
		{
			T x;
			T elements[1];
		};
		constexpr Vec()
			: x(0)
		{}
		constexpr Vec(const T& value)
			: x(value)
		{}

		constexpr inline T& operator[](size_t i)
		{
			TOY_MATH_ASSERT(i < 1, "Index out of bounds");
			return elements[i];
		}
		constexpr inline const T& operator[](size_t i) const
		{
			TOY_MATH_ASSERT(i < 1, "Index out of bounds");
			return elements[i];
		}
		constexpr inline T& get(size_t i)
		{
			TOY_MATH_ASSERT(i < 1, "Index out of bounds");
			return elements[i];
		}
		constexpr inline const T& get(size_t i) const
		{
			TOY_MATH_ASSERT(i < 1, "Index out of bounds");
			return elements[i];
		}

		constexpr inline size_t size() const
		{
			return 1;
		}

		template<size_t From, size_t To>
		constexpr inline Vec<T, MakeSeq<To - From>> subVector() const
		{
			static_assert(From < 1 && To <= 1 && To > From, "subVector out of bounds");
			return subVectorImpl(MakeSeqFromTo<From, To>());
		}
	private:
		template<size_t... Ns>
		constexpr inline Vec<T, MakeSeq<sizeof...(Ns)>> subVectorImpl(const Seq<Ns...>&) const
		{
			return { get(Ns)... };
		}
	};
	template<class T>
	struct Vec<T, MakeSeq<2>>
	{
		typedef Vec<bool, MakeSeq<2>> bool_type;

		union
		{
			struct { T x, y; };
			T elements[2];
		};
		constexpr Vec()
			: x(0),y(0)
		{}
		constexpr Vec(const T& value)
			: x(value), y(value)
		{}
		constexpr Vec(const T& x, const T& y)
			: x(x),y(y)
		{}

		constexpr inline T& operator[](size_t i)
		{
			TOY_MATH_ASSERT(i < 2, "Index out of bounds");
			return elements[i];
		}
		constexpr inline const T& operator[](size_t i) const
		{
			TOY_MATH_ASSERT(i < 2, "Index out of bounds");
			return elements[i];
		}
		constexpr inline T& get(size_t i)
		{
			TOY_MATH_ASSERT(i < 2, "Index out of bounds");
			return elements[i];
		}
		constexpr inline const T& get(size_t i) const
		{
			TOY_MATH_ASSERT(i < 2, "Index out of bounds");
			return elements[i];
		}

		constexpr inline size_t size() const
		{
			return 2;
		}
		template<size_t From, size_t To>
		constexpr inline Vec<T, MakeSeq<To - From>> subVector() const
		{
			static_assert(From < 2 && To <= 2 && To > From, "subVector out of bounds");
			return subVectorImpl(MakeSeqFromTo<From, To>());
		}
	private:
		template<size_t... Ns>
		constexpr inline Vec<T, MakeSeq<sizeof...(Ns)>> subVectorImpl(const Seq<Ns...>&) const
		{
			return { get(Ns)... };
		}
	};
	template<class T>
	struct Vec<T, MakeSeq<3>>
	{
		typedef Vec<bool, MakeSeq<3>> bool_type;
		union
		{
			struct { T x, y, z; };
			T elements[3];
		};
		constexpr Vec()
			: x(0), y(0),z(0)
		{}
		constexpr Vec(const T& value)
			: x(value), y(value), z(value)
		{}
		constexpr Vec(const T& x, const T& y, const T& z)
			: x(x), y(y), z(z)
		{}
		constexpr Vec(const Vec<T,MakeSeq<4>>& v)
			: x(v.x), y(v.y), z(v.z)
		{}

		constexpr inline T& operator[](size_t i)
		{
			TOY_MATH_ASSERT(i < 3, "Index out of bounds");
			return elements[i];
		}
		constexpr inline const T& operator[](size_t i) const
		{
			TOY_MATH_ASSERT(i < 3, "Index out of bounds");
			return elements[i];
		}
		constexpr inline T& get(size_t i)
		{
			TOY_MATH_ASSERT(i < 3, "Index out of bounds");
			return elements[i];
		}
		constexpr inline const T& get(size_t i) const
		{
			TOY_MATH_ASSERT(i < 3, "Index out of bounds");
			return elements[i];
		}

		constexpr inline size_t size() const
		{
			return 3;
		}

		template<size_t From, size_t To>
		constexpr inline Vec<T, MakeSeq<To - From>> subVector() const
		{
			static_assert(From < 3 && To <= 3 && To > From, "subVector out of bounds");
			return subVectorImpl(MakeSeqFromTo<From, To>());
		}
	private:
		template<size_t... Ns>
		constexpr inline Vec<T, MakeSeq<sizeof...(Ns)>> subVectorImpl(const Seq<Ns...>&) const
		{
			return { get(Ns)... };
		}
	};
	template<class T>
	struct Vec<T, MakeSeq<4>>
	{
		typedef Vec<bool, MakeSeq<4>> bool_type;

		union
		{
			struct { T x, y, z, w; };
			T elements[4];
		};
		constexpr Vec()
			: x(0), y(0), z(0), w(0)
		{}
		constexpr Vec(const T& value)
			:x(value), y(value), z(value), w(value)
		{}
		constexpr Vec(const T& x, const T& y, const T& z,const T& w)
			: x(x), y(y), z(z), w(w)
		{}
		constexpr Vec(const Vec<T,MakeSeq<3>>& v)
			: x(v.x), y(v.y), z(v.z), w(1)
		{}
		constexpr inline T& operator[](size_t i)
		{
			TOY_MATH_ASSERT(i < 4, "Index out of bounds");
			return elements[i];
		}
		constexpr inline const T& operator[](size_t i) const
		{
			TOY_MATH_ASSERT(i < 4, "Index out of bounds");
			return elements[i];
		}
		constexpr inline T& get(size_t i)
		{
			TOY_MATH_ASSERT(i < 4, "Index out of bounds");
			return elements[i];
		}
		constexpr inline const T& get(size_t i) const
		{
			TOY_MATH_ASSERT(i < 4, "Index out of bounds");
			return elements[i];
		}

		constexpr inline size_t size() const const
		{
			return 4;
		}

		template<size_t From, size_t To>
		constexpr inline Vec<T, MakeSeq<To - From>> subVector() const
		{
			static_assert(From < 4 && To <= 4 && To > From, "subVector out of bounds");
			return subVectorImpl(MakeSeqFromTo<From, To>());
		}
	private:
		template<size_t... Ns>
		constexpr inline Vec<T, MakeSeq<sizeof...(Ns)>> subVectorImpl(const Seq<Ns...>&) const
		{
			return { get(Ns)... };
		}
	};

	template<size_t N,class T = float> using Vector = Vec<T, MakeSeq<N>>;

	template<class T> using Vector2 = Vector<2, T>;
	template<class T> using Vector3 = Vector<3, T>;
	template<class T> using Vector4 = Vector<4, T>;

	typedef Vector2<float> Vector2f;
	typedef Vector3<float> Vector3f;
	typedef Vector4<float> Vector4f;

	typedef Vector2<int> Vector2i;
	typedef Vector3<int> Vector3i;
	typedef Vector4<int> Vector4i;

	typedef Vector2<unsigned> Vector2u;
	typedef Vector3<unsigned> Vector3u;
	typedef Vector4<unsigned> Vector4u;

	typedef Vector2<double> Vector2d;
	typedef Vector3<double> Vector3d;
	typedef Vector4<double> Vector4d;
}