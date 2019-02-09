#include "workshop.h"

float simple_function(float a, float b)
{
    float x = a * a;
    float y = b * b;
    return (x-y) / (x+y);
}

#pragma omp declare simd
float vector_function(float a, float b)
{
    float x = a * a;
    float y = b * b;
    return (x-y) / (x+y);
}

int main(int argc, char **argv)
{
    const int size = 4;

    auto a = workshop::Array<float>(size);
    auto b = workshop::Array<float>(size);
    auto c = workshop::Array<float>(size);

    for (int i=0; i<size; ++i)
    {
        a[i] = 1.0*(i+1);
        b[i] = 2.5*(i+1);
        c[i] = 0.0;
    }

    auto timer = workshop::start_timer();

    for (int j=0; j<100000; ++j)
    {
        #pragma omp simd
        for (int i=0; i<size; ++i)
        {
            c[i] = simple_function(a[i], b[i]);
        }
    }

    auto duration = workshop::get_duration(timer);

    timer = workshop::start_timer();

    for (int j=0; j<100000; ++j)
    {    
        #pragma omp simd
        for (int i=0; i<size; ++i)
        {
            c[i] = vector_function(a[i], b[i]);
        }
    }

    auto vector_duration = workshop::get_duration(timer);
    auto ops_per_loop = 5;
    auto scalar_gflops  = ops_per_loop * 100000 * size / (duration * 1e3);
    auto vector_gflops  = ops_per_loop * 100000 * size / (vector_duration * 1e3);

    std::cout << "scalar function:" << std::endl
              << "  microseconds: " << duration << std::endl
              << "  gflops: " << scalar_gflops << std::endl;

    std::cout << "vector function:" << std::endl
              << "  microseconds: " << vector_duration << std::endl
              << "  gflops: " << vector_gflops << std::endl;

    return 0;
}
