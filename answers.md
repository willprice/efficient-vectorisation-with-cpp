# Part 1

> Work out the speed of the standard loop and vectorised loop in GFLOPs for your
> computer. How much faster is the vectorised loop compared to the standard
> loop?

When I run `loop` I get these results for vectorized addition:

> The standard loop took 78951.3 microseconds to complete.
> The vectorised loop took 9275.81 microseconds to complete.

We perform 100,000 iterations over an array of 512 elements so the naive loop
operates at 0.65 GFLOPS and the vectorized loop 5.52 GFLOPS.

> Edit loop.cpp and change it so that it compares a standard multiplication with
> a vectorised multiplication (i.e. change c[i] = a[i] + b[i]; to c[i] = a[i] *
> b[i];. Work out the speed in GFLOPs for both loops. Is this similar to the
> speed for addition? Is the vector speed up for multiplication similar to that
> for addition?

For division:

- Naive loop: 91582 microseconds (0.56 GFLOPS)
- Vectorised loop: 16135 microseconds (3.17 GFLOPS)

For multiplication:

- Naive loop: 37373.9 microseconds (1.33 GFLOPS)
- Vectorised loop: 10086 (5.08 GFLOPS)
