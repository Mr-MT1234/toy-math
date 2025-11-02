#pragma once

#include "Logging.h"

#define TOY_MATH_ASSERT_ENABLE
#define TOY_MATH_DEBUG_ASSERT_ENABLE

#define TOY_MATH_BREAK() __debugbreak();

#ifdef TOY_MATH_ASSERT_ENABLE
#define TOY_MATH_ASSERT(x,...) if(!(x)){ TOY_CORE_CRITICAL(__VA_ARGS__);TOY_MATH_BREAK();}
#else
#define TOY_MATH_ASSERT(x,...) 
#endif

#ifdef TOY_MATH_DEBUG_ASSERT_ENABLE
#define TOY_MATH_DEBUG_ASSERT(x,...) if(!(x)){ TOY_CORE_CRITICAL(__VA_ARGS__);TOY_MATH_BREAK();}
#else
#define TOY_MATH_DEBUG_ASSERT(x,...) 
#endif

#define TOY_MATH_STATIC_ASSERT(x,...) StaticAssert<(x)>::Assert()

template<class T>
inline const T& CheckType(const T& t) { return t; }
template<class T>
inline T&& CheckType(T&& t) { return t; }

template<class Type, auto...>
using alwaysType = Type;

template<size_t... Ns> 
struct Sequence
{
	template<size_t N> 
	using append = Sequence<N, Ns...>;
};

template<size_t N,size_t... Ns>
struct _make_sequence
{
	typedef typename _make_sequence<N - 1, N, Ns...>::sequence sequence;
};
template<size_t... Ns>
struct _make_sequence<0,Ns...>
{
	typedef Sequence<0,Ns...> sequence;
};

template<size_t From, size_t... Ns> struct _make_sequence_from_to;

template<size_t From, size_t N, size_t... Ns>
struct _make_sequence_from_to<From,N,Ns...>
{
	static_assert(N > From, "From should be greater than To");
	typedef typename _make_sequence_from_to<From,N - 1, N, Ns...>::sequence sequence;
};
template<size_t From, size_t... Ns>
struct _make_sequence_from_to<From,From, Ns...>
{
	typedef Sequence<From, Ns...> sequence;
};

template<size_t N>
using MakeSequence = typename _make_sequence<N - 1>::sequence;
template<size_t From,size_t To>
using MakeSequenceFromTo = typename _make_sequence_from_to<From,To - 1>::sequence;

