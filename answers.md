# Part 1

> Work out the speed of the standard loop and vectorised loop in GFLOPs for your
> computer. How much faster is the vectorised loop compared to the standard
> loop?

When I run `loop` I get these results for vectorized addition:

> The standard loop took 78951.3 microseconds to complete.
> The vectorised loop took 9275.81 microseconds to complete.

We perform 100,000 iterations over an array of 512 elements so the naive loop
operates at 0.65 GFLOPS and the vectorized loop 5.52 GFLOPS.
