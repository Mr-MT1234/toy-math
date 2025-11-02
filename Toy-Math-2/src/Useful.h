#pragma once

#include "VectorOperations.h"

namespace Toy::Math
{
    extern double PI;
    extern double E;

    constexpr inline long double operator""rad(long double f)
    {
        return f * PI / 180;
    }
    constexpr inline long double operator""rad(unsigned long long f)
    {
        return f * PI / 180;
    }
    

    constexpr inline long double operator""deg(long double f)
    {                                      
        return f / PI * 180;               
    }                                      
    constexpr inline long double operator""deg(unsigned long long f)
    {                                      
        return f / PI * 180;               
    }                                      
    

    constexpr inline float Radient(float deg)
    {
        return deg * PI / 180;
    }
    constexpr inline float Degrees(float deg)
    {
        return deg / PI * 180;
    }

    template<class T,size_t... Ns>
    constexpr inline Vec<T, Seq<Ns...>> Radient(Vec<T,Seq<Ns...>> deg)
    {
        return deg * PI / 180;
    }
    template<class T, size_t... Ns>
    constexpr inline Vec<T, Seq<Ns...>> Degrees(Vec<T, Seq<Ns...>> deg)
    {
        return deg / PI * 180;
    }
}