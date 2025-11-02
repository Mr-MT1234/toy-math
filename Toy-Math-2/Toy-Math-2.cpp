#include "Logging.h"
#include "Vectors.h"
#include "VectorOperations.h"
#include "Matrices.h"
#include "MatrixOperations.h"
#include "Transformation.h"
#include "Useful.h"

#include <chrono>
#include <string>
#include <array>
#include <immintrin.h>

using namespace Toy::Math;


struct Timer
{
    typedef std::chrono::high_resolution_clock::time_point TimePoint;
    typedef std::chrono::high_resolution_clock::duration Duration;

    Timer(const std::string& name)
        :name(name),begin(std::chrono::high_resolution_clock::now())
    {}
    ~Timer()
    {
        TimePoint end = std::chrono::high_resolution_clock::now();
        Duration duration = end - begin;

        TOY_CORE_TRACE("\"%s\" finished after : %fns (%fms)",name.c_str(),duration.count() / 1000.f, duration.count() / 1000000.0);
    }

private:
    std::string name;
    TimePoint begin;
};

void DoNotOptemize(Vector4f& v);

int main()
{    
    using namespace std::string_literals;

    constexpr size_t IterationCount = 10;
    constexpr size_t size = 10000000;

    Vector4f* vectors1 = new Vector4f[size];
    Vector4f* vectors2 = new Vector4f[size];

    Vector4f v;
    for (size_t i = 0; i < size; i++)
    {
        vectors1[i] = { 70 };
    }
    for (size_t i = 0; i < size; i++)
    {
        vectors2[i] = { 30 };
    }
    for(size_t Iteration = 1;Iteration <= IterationCount; Iteration++)
    {
        Timer t("Addition "s + std::to_string(Iteration) + "/" + std::to_string(IterationCount));

        for (size_t i = 0; i < size; i++)
        {
            v = vectors1[i] + vectors2[i];
        }
    }

    DoNotOptemize(v);
    TOY_CORE_INFO("Didn't crash !!!");
}

