#include "workshop.h"

int main(int argc, char **argv)
{
    int size = 512;

    auto a = workshop::Array<workshop::Point>(size);
    auto b = workshop::Array<workshop::Point>(size);
    auto c = workshop::Array<float>(size);

    for (int i=0; i<size; ++i)
    {
        a[i] = workshop::Point(i,i+1,i+2);
        b[i] = workshop::Point(2*i, 2*i+1, 2*i+2);
        c[i] = 0;
    }

    auto timer = workshop::start_timer();

    for (int j=0; j<100000; ++j)
    {
        for (int i=0; i<size; ++i)
        {
            float dx = a[i].x - b[i].x;
            float dy = a[i].y - b[i].y;
            float dz = a[i].z - b[i].z;

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
            float dx = a[i].x - b[i].x;
            float dy = a[i].y - b[i].y;
            float dz = a[i].z - b[i].z;

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
