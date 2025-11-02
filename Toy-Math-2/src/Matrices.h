#pragma once

#include "Defines.h"
#include "Vectors.h"

namespace Toy::Math
{
	template<class T, class RSeq, class CSeq> struct Mat;

	template<class T,size_t... Rows, size_t... Columns>
	struct Mat<T, Seq<Rows...>, Seq<Columns...>>
	{
		typedef Mat<bool, Seq<Rows...>, Seq<Columns...>> bool_type;
		typedef Vector<sizeof...(Columns), T> row_type;
		typedef Vector<sizeof...(Rows), T> column_type;
		typedef T type;

		row_type rows[sizeof...(Rows)];

		constexpr Mat(const T& scale = 1)
			: rows{ (getIdentityVec<Rows>(scale))... }
		{}
		constexpr Mat(const alwaysType<row_type,Rows>&... rows)
			: rows{rows...}
		{}
		template<size_t... oRs,size_t... oCs>
		constexpr Mat(const Mat<T, Seq<oRs...>, Seq<oCs...>>& other)
			: rows{ getIdentityVec<Rows>(1)... }
		{
			for (size_t r = 0; r < sizeof...(Rows); r++)
			{
				for (size_t c = 0; c < sizeof...(Columns) && c < sizeof...(oCs); c++)
				{
					rows[r][c] = other[r][c];
				}
			}
		}

		constexpr inline column_type getColumn(size_t i) const
		{
			TOY_MATH_ASSERT(i < sizeof...(Columns), "Index out of bounds");
			return { (rows[Rows][i])... };
		}
		constexpr inline void getColumn(size_t i, column_type& dst) const
		{
			TOY_MATH_ASSERT(i < sizeof...(Columns), "Index out of bounds");
			((dst[Rows] = rows[Rows][i]),...);
		}
		constexpr inline row_type& getRow(size_t i)
		{
			TOY_MATH_ASSERT(i < sizeof...(Rows), "Index out of bounds");
			return rows[i];
		}
		constexpr inline const row_type& getRow(size_t i) const
		{
			TOY_MATH_ASSERT(i < sizeof...(Rows), "Index out of bounds");
			return rows[i];
		}

		constexpr inline row_type& operator[](size_t i)
		{
			TOY_MATH_ASSERT(i < sizeof...(Rows), "Index out of bounds");
			return rows[i];
		}
		constexpr inline const row_type& operator[](size_t i) const
		{
			TOY_MATH_ASSERT(i < sizeof...(Rows), "Index out of bounds");
			return rows[i];
		}

		constexpr inline size_t getRowsNumber() { return sizeof...(Rows); }
		constexpr inline size_t getColumnssNumber() { return sizeof...(Columns); }
		constexpr inline size_t getElementssNumber() { return sizeof...(Rows) * sizeof...(Columns); }

		template<size_t FromR,size_t FromC,size_t ToR,size_t ToC>
		constexpr inline Mat<T,MakeSeq<ToR - FromR>, MakeSeq<ToC - FromC>> subMatrix() const
		{
			return subMatrixImpl<FromC, ToC>(MakeSeqFromTo<FromR, ToR>());
		}
	private:
		template<size_t From,size_t To,size_t... RSeq>
		constexpr inline Mat<T,MakeSeq<sizeof...(RSeq)>, MakeSeq<To - From>> subMatrixImpl(const Seq<RSeq...>&) const
		{
			return { (getRow(RSeq).subVector<From,To>())... };
		}

		template<size_t I>
		constexpr inline row_type getIdentityVec(const T& scale)
		{
			return { (I == Columns ? (T)scale : (T)0)... };
		}
		template<size_t I,class T,size_t... Ns>
		constexpr inline row_type TrimVec(const Vec<T,Seq<Ns...>>& v)
		{
			return { (Columns < sizeof...(Ns) ? v[Columns] : (I == Columns ? (T)1 : (T)0))... };
		}
	};

	template<size_t R,size_t C,class T = float>
	using Matrix = Mat<T, MakeSeq<R>, MakeSeq<C>>;

	template<class T>
	using Matrix2 = Mat<T, MakeSeq<2>, MakeSeq<2>>;
	template<class T>
	using Matrix3 = Mat<T, MakeSeq<3>, MakeSeq<3>>;
	template<class T>
	using Matrix4 = Mat<T, MakeSeq<4>, MakeSeq<4>>;

	typedef Matrix2<float> Matrix2f;
	typedef Matrix3<float> Matrix3f;
	typedef Matrix4<float> Matrix4f;

	typedef Matrix2<int> Matrix2i;
	typedef Matrix3<int> Matrix3i;
	typedef Matrix4<int> Matrix4i;

	typedef Matrix2<unsigned> Matrix2u;
	typedef Matrix3<unsigned> Matrix3u;
	typedef Matrix4<unsigned> Matrix4u;

	typedef Matrix2<double> Matrix2d;
	typedef Matrix3<double> Matrix3d;
	typedef Matrix4<double> Matrix4d;
}