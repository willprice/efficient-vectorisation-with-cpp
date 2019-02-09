#include "workshop.h"
#include <string>
#ifndef SIZE
#define SIZE 16
#endif

int main(int argc, char **argv)
{
    const int size = SIZE;

    auto a = new float[size][size];
    auto b = new float[size][size];

    auto c = new float[size][size];

    for (int i=0; i<size; ++i)
    {
        for (int j=0; j<size; ++j)
        {
            a[i][j] = 1+i*j;
            b[i][j] = 1+i+j;
        }
    }

    auto timer = workshop::start_timer();

    for (int k=0; k<10000; ++k)
    {
        for (int i=0; i<size; ++i)
        {
            for (int j=0; j<size; ++j)
            {
                c[i][j] = a[i][j] / b[i][j];
            }
        }
    }

    auto duration = workshop::get_duration(timer);

    timer = workshop::start_timer();

    for (int k=0; k<10000; ++k)
    {
        #pragma omp simd
        for (int i=0; i<size; ++i)
        {
            for (int j=0; j<size; ++j)
            {
                c[i][j] = a[i][j] / b[i][j];
            }
        }
    }

    auto outer_duration = workshop::get_duration(timer);

    timer = workshop::start_timer();

    for (int k=0; k<10000; ++k)
    {
        for (int i=0; i<size; ++i)
        {
            #pragma omp simd
            for (int j=0; j<size; ++j)
            {
                c[i][j] = a[i][j] / b[i][j];
            }
        }
    }

    auto inner_duration = workshop::get_duration(timer);

    timer = workshop::start_timer();

    for (int k=0; k<10000; ++k)
    {
        #pragma omp simd collapse(2)
        for (int i=0; i<size; ++i)
        {
            for (int j=0; j<size; ++j)
            {
                c[i][j] = a[i][j] / b[i][j];
            }
        }
    }

    auto collapse_duration = workshop::get_duration(timer);
    auto gflops = 10000 * size * (size / (duration * 1e3));
    auto outer_gflops = 10000 * size * (size / (outer_duration * 1e3));
    auto inner_gflops = 10000 * size * (size / (inner_duration * 1e3));
    auto collapse_gflops = 10000 * size * (size / (collapse_duration * 1e3));

    std::cout << "array size: " << size << std::endl;
    std::cout << "standard loop:" << std::endl
              << "  microseconds: " << duration << std::endl
              << "  gflops: " << gflops << std::endl;

    std::cout << "vectorized outer loop:" << std::endl
              << "  microseconds: " << outer_duration << std::endl
              << "  gflops: " << outer_gflops << std::endl;

    std::cout << "vectorized inner loop:" << std::endl
              << "  microseconds: " << inner_duration << std::endl
              << "  gflops: " << inner_gflops << std::endl;

    std::cout << "vectorized collapsed loop:" << std::endl
              << "  microseconds: " << collapse_duration << std::endl
              << "  gflops: " << collapse_gflops << std::endl;

    return 0;
}
