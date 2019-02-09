#include "workshop.h"

int main(int argc, char **argv)
{
    int size = 512;

    auto ax = workshop::Array<float>(size);
    auto ay = workshop::Array<float>(size);
    auto az = workshop::Array<float>(size);

    auto bx = workshop::Array<float>(size);
    auto by = workshop::Array<float>(size);
    auto bz = workshop::Array<float>(size);

    auto c = workshop::Array<float>(size);

    for (int i=0; i<size; ++i)
    {
        ax[i] = i;
        ay[i] = i+1;
        az[i] = i+2;

        bx[i] = 2*i;
        by[i] = 2*i+1;
        bz[i] = 2*i+2;

        c[i] = 0;
    }

    auto timer = workshop::start_timer();

    for (int j=0; j<100000; ++j)
    {
        for (int i=0; i<size; ++i)
        {
            float dx = ax[i] - bx[i];
            float dy = ay[i] - by[i];
            float dz = az[i] - bz[i];

            c[i] = dx*dx + dy*dy + dz*dz;
        }
    }

    auto duration = workshop::get_duration(timer);

    timer = workshop::start_timer();

    for (int j=0; j<100000; ++j)
    {
        #pragma omp simd
        for (int i=0; i<size; ++i)
        {
            float dx = ax[i] - bx[i];
            float dy = ay[i] - by[i];
            float dz = az[i] - bz[i];

            c[i] = dx*dx + dy*dy + dz*dz;
        }
    }

    auto vector_duration = workshop::get_duration(timer);

    std::cout << "The standard loop took " << duration
              << " microseconds to complete." << std::endl;

    std::cout << "The vectorised loop took " << vector_duration
              << " microseconds to complete." << std::endl;    

    return 0;
}
