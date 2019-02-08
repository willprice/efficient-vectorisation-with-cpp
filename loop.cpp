#include "workshop.h"

int main(int argc, char **argv)
{
    const int size = 512;

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
        for (int i=0; i<size; ++i)
        {
            c[i] = a[i] + b[i];
        }
    }

    auto duration = workshop::get_duration(timer);

    timer = workshop::start_timer();

    for (int j=0; j<100000; ++j)
    {    
        #pragma omp simd
        for (int i=0; i<size; ++i)
        {
            c[i] = a[i] + b[i];
        }
    }

    auto vector_duration = workshop::get_duration(timer);
    auto gflops = 100000 * size / (duration * 1e3);
    auto vectorised_gflops = 100000 * size / (vector_duration * 1e3);

    std::cout << "The standard loop took " << duration
              << " microseconds to complete."
              << " (" << gflops << " GFLOPS)" << std::endl;

    std::cout << "The vectorised loop took " << vector_duration
              << " microseconds to complete"
              << " (" << vectorised_gflops << " GFLOPS)" << std::endl;

    return 0;
}
