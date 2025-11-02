#pragma once

#include "Matrices.h"
#include "VectorOperations.h"

#define MAT  Mat<T,Seq<Rs...>, Seq<Cs...>>
#define MAT_S(Rs,Cs)  Mat<T,Seq<Rs...>, Seq<Cs...>>

namespace Toy::Math
{
#pragma region General

	template<class T, size_t... Rs, size_t... Cs>
	constexpr inline MAT_S(Cs, Rs) Transpose(const MAT_S(Rs, Cs)& mat)
	{
		return { (mat.getColumn(Cs))... };
	}

	template<class T, size_t... Rs, size_t... Cs,  size_t... oCs>
	constexpr inline  MAT_S(Rs,oCs) operator*(const MAT_S(Rs, Cs)& left, const MAT_S(Cs, oCs)& right)
	{
		typedef Vec<T,Seq<Cs...>> Vec;

		MAT_S(Rs, oCs) result;
		auto tRight = Transpose(right);

		for (size_t row = 0; row < sizeof...(Rs); row++)
		{
			const Vec& rowVec = left[row];
			for (size_t column = 0; column < sizeof...(oCs); column++)
			{
				result[row][column] = Dot(rowVec, tRight[column]);
			}
		}

		return result;
	}
	template<class T, size_t... Rs, size_t... Cs>
	constexpr inline Vec<T,Seq<Cs...>> operator*(const MAT_S(Rs, Cs)& left, const Vec<T,Seq<Cs...>>& right)
	{
		typedef Vec<T, Seq<Cs...>> Vector;

		Vector result;

		for (size_t row = 0; row < sizeof...(Rs); row++)
		{
			result[row] = Dot(left[row], right);
		}

		return result;
	}
	template<class T, size_t... Rs, size_t... Cs>
	constexpr inline MAT operator*(const MAT& left, const T& s)
	{
		return { (left[Rs] * s)... };
	}

	template<class T, size_t... Rs, size_t... Cs>
	constexpr inline MAT operator+(const MAT& left, const MAT& right)
	{
		return { (left[Rs] + right[Rs])... };
	}
	template<class T, size_t... Rs, size_t... Cs>
	constexpr inline MAT operator-(const MAT& left, const MAT& right)
	{
		return { (left[Rs] - right[Rs])... };
	}
	template<class T, size_t... Rs, size_t... Cs>
	constexpr inline MAT operator-(const MAT& left, const T& s)
	{
		return { (left[Rs] * s)... };
	}

	template<class T, size_t... Rs, size_t... Cs>
	constexpr inline MAT CompMult(const MAT& left, const MAT& right)
	{
		return { (left[Rs] * right[Rs])... };
	}

	template<class T, size_t... Rs>
	constexpr inline MAT_S(Rs,Rs) Inverse(const MAT_S(Rs, Rs)& mat)
	{
		constexpr size_t RowCount = sizeof...(Rs);
		typedef Matrix<RowCount, RowCount * 2, T> Mat;

		Mat inverse(mat);
		((inverse[Rs][(Rs) + RowCount] = 1),...);

		for (size_t row = 0; row < RowCount; row++)
		{
			TOY_MATH_ASSERT((inverse[row][row] != 0), "Matrix is ininvertable");
			inverse[row] /= inverse[row][row];

			for (size_t row2 = 0; row2 < RowCount; row2++)
			{
				if (row2 == row)
					continue;

				inverse [row2] -= inverse[row2][row] * inverse[row];
			}
		}

		return inverse.subMatrix<0,RowCount,RowCount,RowCount * 2>();
	}

#pragma endregion
#pragma region Compound Assignement

	template<class T, size_t... Rs, size_t... Cs>
	constexpr MAT_S(Rs, Cs)& operator*=(MAT_S(Rs, Cs)& left, const MAT_S(Cs, Cs)& right)
	{
		typedef Vec<T, Seq<Cs...>> Vec;

		auto tRight = Transpose(right);

		for (size_t row = 0; row < sizeof...(Rs); row++)
		{
			Vec rowVec = left[row];
			for (size_t column = 0; column < sizeof...(Cs); column++)
			{
				left[row][column] = Dot(rowVec, tRight[column]);
			}
		}

		return left;
	}

	template<class T, size_t... Rs, size_t... Cs>
	constexpr MAT& operator+=(MAT& left, const MAT& right)
	{
		((left[Rs] += right[Rs]),...);
		return left;
	}
	template<class T, size_t... Rs, size_t... Cs>
	constexpr MAT& operator-=(MAT& left, const MAT& right)
	{
		((left[Rs] -= right[Rs]),...);
		return left;
	}
	template<class T, size_t... Rs, size_t... Cs>
	constexpr MAT& operator*=(MAT& left, const T& s)
	{
		((left[Rs] *= s),...);
		return left;
	}

#pragma endregion

#pragma region Exeptions



#pragma endregion

}

#undef MAT
#undef MAT_S(Rs,Cs)