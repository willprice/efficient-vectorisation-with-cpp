#include "workshop.h"
#include <string>

void print_result(const std::string& type, double duration, double gflops) {
    std::cout << type << ":" << std::endl
              << "  duration: " << duration << std::endl
              << "  gflops: " << gflops << std::endl;
}

int main(int argc, char **argv)
{
    int size = 512;
    if (argc > 1) {
      size = std::stoi(argv[1]);
    }
    std::cout << "Array size " << size << std::endl;


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
            c[i] = a[i] * b[i];
        }
    }

    auto duration = workshop::get_duration(timer);

    timer = workshop::start_timer();

    for (int j=0; j<100000; ++j)
    {    
        #pragma omp simd
        for (int i=0; i<size; ++i)
        {
            c[i] = a[i] * b[i];
        }
    }

    auto vector_duration = workshop::get_duration(timer);
    auto gflops = 100000 * size / (duration * 1e3);
    auto vector_gflops = 100000 * size / (vector_duration * 1e3);

    print_result("naive", duration, gflops);
    print_result("vectorised", vector_duration, vector_gflops);
    return 0;
}
