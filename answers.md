# Part 1

> Work out the speed of the standard loop and vectorised loop in GFLOPs for your
> computer. How much faster is the vectorised loop compared to the standard
> loop?

When I run `loop` I get these results for vectorized addition:

> The standard loop took 78951.3 microseconds to complete.
> The vectorised loop took 9275.81 microseconds to complete.

We perform 100,000 iterations over an array of 512 elements so the scalar loop
operates at 0.65 GFLOPS and the vectorized loop 5.52 GFLOPS.

> Edit loop.cpp and change it so that it compares a standard multiplication with
> a vectorised multiplication (i.e. change c[i] = a[i] + b[i]; to c[i] = a[i] *
> b[i];. Work out the speed in GFLOPs for both loops. Is this similar to the
> speed for addition? Is the vector speed up for multiplication similar to that
> for addition?

For division:

- Scalar loop: 91582 microseconds (0.56 GFLOPS)
- Vectorised loop: 16135 microseconds (3.17 GFLOPS)

For multiplication:

- Scalar loop: 37373.9 microseconds (1.33 GFLOPS)
- Vectorised loop: 10086 (5.08 GFLOPS)

> Finally, edit loop.cpp to change the size of the arrays (edit the size
> variable). Does changing the size affect the speed of the two loops in GFLOPs?
> Does changing the size affect the speedup of the vectorised loop versus the
> unvectorised loop? Good sizes to try are 1, 2, 4, 128, 256 and 4096.

| Array size | Scalar duration | Scalar GFLOPS | Vector duration | Vector GFLOPS |
|------------|----------------|--------------|-----------------|---------------|
| 1 | 743.194 | 0.134554 | 1546.23 | 0.0646733 |
| 2 | 823.174 | 0.242962 | 1958.97 | 0.102095 |
| 4 | 555.532 | 0.720031 | 308.598 | 1.29618 |
| 8 | 841.847 | 0.950291 | 299.219 | 2.67363 |
| 16 | 1248.97 | 1.28105 | 437.012 | 3.66123 |
| 32 | 2170.01 | 1.47465 | 578.711 | 5.52953 |
| 64 | 5030.23 | 1.27231 | 992.67 | 6.44726 |
| 128 | 7927.98 | 1.61454 | 2007.57 | 6.37586 |
| 256 | 19931 | 1.28443 | 6036.95 | 4.24055 |
| 512 | 38305.4 | 1.33662 | 9322.71 | 5.49196 |
| 1024 | 83866.9 | 1.22098 | 21142.1 | 4.84343 |
| 2048 | 167905 | 1.21974 | 42595.4 | 4.80803 |
| 4096 | 349977 | 1.17036 | 116263 | 3.52304 |
