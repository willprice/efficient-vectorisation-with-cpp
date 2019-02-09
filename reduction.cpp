#include "workshop.h"
#include <string>

int main(int argc, char **argv)
{
    
    int size = 512;
    if (argc > 1) {
      size = std::stoi(argv[1]);
    }

    auto a = workshop::Array<float>(size);
    auto b = workshop::Array<float>(size);

    for (int i=0; i<size; ++i)
    {
        a[i] = 1.0*(i+1);
        b[i] = 2.5*(i+1);
    }

    auto timer = workshop::start_timer();

    float total;

    for (int j=0; j<100000; ++j)
    {
        total = 0;

        for (int i=0; i<size; ++i)
        {
            total += a[i] + b[i];
        }
    }

    auto duration = workshop::get_duration(timer);

    timer = workshop::start_timer();

    float vec_total;

    for (int j=0; j<100000; ++j)
    {    
        vec_total = 0;

        #pragma omp simd
        for (int i=0; i<size; ++i)
        {
            vec_total += a[i] + b[i];
        }
    }

    auto vector_duration = workshop::get_duration(timer);

    timer = workshop::start_timer();

    float red_total;

    for (int j=0; j<100000; ++j)
    {
        red_total = 0;

        #pragma omp simd reduction(+:red_total)
        for (int i=0; i<size; ++i)
        {
            red_total += a[i] + b[i];
        }
    }

    auto red_duration = workshop::get_duration(timer);
    auto standard_gflops = 100000 * size / (duration * 1e3);
    auto vector_gflops = 100000 * size / (vector_duration * 1e3);
    auto reduction_gflops = 100000 * size / (red_duration * 1e3);

    std::cout << "array size: " << size << std::endl;
    std::cout << "standard loop:" << std::endl
              << "  total: " << total << std::endl
              << "  microseconds: " << duration << std::endl
              << "  gflops: " << standard_gflops << std::endl;

    std::cout << "vectorised loop:" << std::endl
              << "  total: " << vec_total << std::endl
              << "  microseconds: " << vector_duration << std::endl
              << "  gflops: " << vector_gflops << std::endl;

    std::cout << "reduction:" << std::endl
              << "  total: " << red_total << std::endl
              << "  microseconds: " << red_duration << std::endl
              << "  gflops: " << reduction_gflops << std::endl;

    return 0;
}
