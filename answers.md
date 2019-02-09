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

> Find out the speed, number of cores and size of vector of the processor you
> are using now (e.g. by using the lscpu command on Linux, and multiplying the
> number of sockets by the number of cores per socket, and then looking at the
> file /proc/cpuinfo and seeing if sse, sse2, avx or avx2 etc. are included in
> the set of supported processor flags).

```
$ lscpu

Architecture:        x86_64
CPU op-mode(s):      32-bit, 64-bit
Byte Order:          Little Endian
Address sizes:       39 bits physical, 48 bits virtual
CPU(s):              4
On-line CPU(s) list: 0-3
Thread(s) per core:  2
Core(s) per socket:  2
Socket(s):           1
NUMA node(s):        1
Vendor ID:           GenuineIntel
CPU family:          6
Model:               78
Model name:          Intel(R) Core(TM) i5-6300U CPU @ 2.40GHz
Stepping:            3
CPU MHz:             1300.066
CPU max MHz:         3000.0000
CPU min MHz:         400.0000
BogoMIPS:            4993.00
Virtualization:      VT-x
L1d cache:           32K
L1i cache:           32K
L2 cache:            256K
L3 cache:            3072K
NUMA node0 CPU(s):   0-3
Flags:               fpu vme de pse tsc msr pae mce cx8 apic sep mtrr pge mca cmov pat pse36 clflush dts acpi mmx fxsr sse sse2 ss ht tm pbe syscall nx pdpe1gb rdtscp lm constant_tsc art arch_perfmon pebs bts rep_good nopl xtopology nonstop_tsc cpuid aperfmperf tsc_known_freq pni pclmulqdq dtes64 monitor ds_cpl vmx smx est tm2 ssse3 sdbg fma cx16 xtpr pdcm pcid sse4_1 sse4_2 x2apic movbe popcnt tsc_deadline_timer aes xsave avx f16c rdrand lahf_lm abm 3dnowprefetch cpuid_fault epb invpcid_single pti ssbd ibrs ibpb stibp tpr_shadow vnmi flexpriority ept vpid ept_ad fsgsbase tsc_adjust bmi1 hle avx2 smep bmi2 erms invpcid rtm mpx rdseed adx smap clflushopt intel_pt xsaveopt xsavec xgetbv1 xsaves dtherm ida arat pln pts hwp hwp_notify hwp_act_window hwp_epp flush_l1d
```

So I have 2 cores running at a max of 3GHz which support the SSE, SSE2, AVX,
AVX2 instruction sets.

Max FLOPS of my computer:

AVX2 implements 256 bit vector units, which can fit 8 floats.

- Serial Scalar: 3 * 1e9 = 3 GFLOP/s
- Serial Vectorized: 3 * 1e9 * 8 = 24 GFLOP/s
- Parallel Scalar: 3 * 1e9 * 2 = 6 GFLOP/s
- Parallel Vectorised: 3 * 1e9 * 2 * 8 = 48 GFLOP/s

Andrei says these things about the above calculations:

> Your calculation needs an extra 2x because your CPU can do [FMA](https://en.wikipedia.org/wiki/Multiply%E2%80%93accumulate_operation#Fused_multiply%E2%80%93add)s
> calculation needs an extra 2x because your CPU can do FMAs (`Flags: fma`)

> Some CPUs also have more than 1 vector unit/core, and I don't know how many yours has
> a TX2, for example, has 2 vector units per core, so you would have an extra 2x

> Turbo frequency is also a bit of black magic at the very bottom of that
> [page](https://en.wikichip.org/wiki/intel/core_i5/i5-6300u) you will see that
> it's different if you're running 1 vs 2 cores

> When you use AVX, frequency also drops further (by an usually unspecified amount)
> it's safe to assume at least -200 MHz for AVX2 and more if there was AVX-512.

---

> Edit loop.cpp and use omp simd to vectorise the standard loop. Check that the
> newly-vectorised standard loop now runs at the same speed as the vectorised
> loop.

The first loop still runs a bit slower, I wonder if this is due to cache warming effects?

> For GCC, omp simd vectorisation is supported via the -fopenmp-simd compiler
> flag. For CLANG, omp simd vectorisation is supported via the -openmp-simd
> compiler flag. Try recompiling loop.cpp without this flag.

The second loop still runs ~ 0.4GFLOP/s faster, but is considerably slower than
it was before. I think this points to cache effects causing the first loop to be slower.

> How fast do the two loops run now? Does this mean that #pragma omp simd has been ignored?

- First loop: ~ 0.9 GFLOP/s
- Second loop: ~ 1.3 GFLOP/s

Looks like the pragma is being ignored as I was getting ~5.5 GFLOP/s before.

## `pragma omp simd reduction(+:var)`

> Compile and run this code for different values of size. How does the speed-up
> from using vectorisation and vectorised reduction change?

| Array size | scalar time | scalar GFLOP/s | vector time | vector GFLOP/s | reduction time | reduction GFLOP/s |
|------------|-------------|----------------|-------------|----------------|----------------|-------------------|
| 1 | 502 | 0.199203 | 505.65 | 0.197765 | 2347.99 | 0.0425896 |
| 2 | 937.138 | 0.213416 | 842.097 | 0.237502 | 2092.84 | 0.0955638 |
| 4 | 1283.77 | 0.311582 | 601.674 | 0.664812 | 3510.95 | 0.113929 |
| 8 | 2029.66 | 0.394155 | 1048.83 | 0.762751 | 2339.87 | 0.341899 |
| 16 | 2507.49 | 0.638087 | 1026.28 | 1.55903 | 2264.72 | 0.70649 |
| 32 | 6287.35 | 0.508959 | 2594.49 | 1.23338 | 2802.2 | 1.14196 |
| 64 | 15240.4 | 0.419938 | 6754.56 | 0.947507 | 3841.41 | 1.66605 |
| 128 | 35385.2 | 0.361734 | 16178.5 | 0.791175 | 5838 | 2.19253 |
| 256 | 75384 | 0.339595 | 39026.9 | 0.655958 | 10401.2 | 2.46126 |
| 512 | 155879 | 0.32846 | 86662.7 | 0.590796 | 19019.6 | 2.69195 |
| 1024 | 316962 | 0.323067 | 177706 | 0.576233 | 36510.5 | 2.80467 |
| 2048 | 628627 | 0.325789 | 368496 | 0.555772 | 72284 | 2.83327 |
| 4096 | 1.26911e+06 | 0.322745 | 734218 | 0.557873 | 143426 | 2.85583 |


## `pragma omp declare simd`

With inlining enabled:

| Array size | Scalar time | Scalar GFLOP/s | Vector time | Vector GFLOP/s |
|------------|-------------|----------------|-------------|----------------|
| 1 | 1291.97 | 0.387006 | 1203.12 | 0.415587 |
| 2 | 2456.61 | 0.407065 | 2750.01 | 0.363636 |
| 4 | 385.767 | 5.18448 | 385.77 | 5.18444 |
| 8 | 471.972 | 8.47508 | 442.435 | 9.04088 |
| 16 | 879.353 | 9.0976 | 773.301 | 10.3453 |
| 32 | 1241.08 | 12.892 | 1232.55 | 12.9812 |
| 64 | 2386.75 | 13.4073 | 2405.94 | 13.3004 |
| 128 | 4937.28 | 12.9626 | 4988.76 | 12.8288 |
| 256 | 9848.82 | 12.9965 | 7809.74 | 16.3898 |
| 512 | 17391.1 | 14.7202 | 16013.2 | 15.9869 |
| 1024 | 34117.6 | 15.0069 | 33555.8 | 15.2582 |
| 2048 | 67252.7 | 15.2262 | 64019.7 | 15.9951 |
| 4096 | 134780 | 15.1952 | 135884 | 15.0717 |

Without inlining enabled

| Array size | Scalar time | Scalar GFLOP/s | Vector time | Vector GFLOP/s |
|------------|-------------|----------------|-------------|----------------|
| 1 | 4800.88 | 0.104148 | 3785.86 | 0.13207 |
| 2 | 7881.58 | 0.126878 | 7589.06 | 0.131769 |
| 4 | 5377.92 | 0.371891 | 4476.73 | 0.446755 |
| 8 | 5683.05 | 0.703847 | 5682.35 | 0.703935 |
| 16 | 11169.8 | 0.716215 | 11037.5 | 0.724802 |
| 32 | 20788.1 | 0.769671 | 20806.8 | 0.76898 |
| 64 | 40497.9 | 0.790165 | 40885.4 | 0.782676 |
| 128 | 78327.9 | 0.817078 | 78274.8 | 0.817632 |
| 256 | 156083 | 0.820074 | 158938 | 0.805346 |
| 512 | 307416 | 0.832747 | 320011 | 0.799971 |
| 1024 | 617820 | 0.82872 | 640569 | 0.79929 |
| 2048 | 1.21797e+06 | 0.840742 | 1.27857e+06 | 0.800895 |
| 4096 | 2.45241e+06 | 0.835096 | 2.57984e+06 | 0.793848 |

> What is the speed-up of the vector function versus the scalar function?

Negligible on my machine regardless of inlining or not.

> What is the difference in speed between the inlined and non-inlined program?

Inlining makes a huge difference, making it about ~20 times faster.

## `pragma omp simd collapse(n)`

> Run this code for different values of size to compare the speed-up (if any)
> of vectorising the double loop in these different ways.

| Array size | Scalar time | Scalar GFLOP/s | Vector outer-loop time | Vector outer-loop GFLOP/s | Vector inner-loop time | Vector inner-loop GFLOP/s | Vector collapsed time | Vector collapsed GFLOP/s |
|------------|-------------|----------------|------------------------|---------------------------|------------------------|---------------------------|-----------------------|--------------------------|
| 1 | 0.113 | 88.4956 | 0.055 | 181.818 | 0.052 | 192.308 | 0.05 | 200 |
| 2 | 0.14 | 285.714 | 0.055 | 727.273 | 0.037 | 1081.08 | 80.298 | 0.498144 |
| 4 | 229.415 | 0.697426 | 229.273 | 0.697858 | 115.768 | 1.38207 | 460.736 | 0.34727 |
| 8 | 957.218 | 0.668604 | 916.499 | 0.69831 | 229.193 | 2.79241 | 1712.72 | 0.373675 |
| 16 | 3665.17 | 0.698467 | 3352.99 | 0.763497 | 826.001 | 3.09927 | 5922.55 | 0.432246 |
| 32 | 17187.2 | 0.595792 | 13229.4 | 0.774031 | 3397.86 | 3.01366 | 26257.6 | 0.389982 |
| 64 | 49763.6 | 0.823092 | 45493.1 | 0.900356 | 11137 | 3.67782 | 87999.6 | 0.465457 |
| 128 | 187922 | 0.871851 | 189359 | 0.865237 | 48695 | 3.36461 | 432157 | 0.379121 |
| 256 | 847053 | 0.773694 | 820065 | 0.799156 | 227145 | 2.88521 | 1.81143e+06 | 0.361791 |
| 512 | 3.94705e+06 | 0.664151 | 3.8304e+06 | 0.684378 | 1.37667e+06 | 1.90419 | 6.58155e+06 | 0.398301 |

> Do you see any speed-up from using collapse(2)? Which method of vectorising a
> double loop reliably performs best?

A few observations:

- Array sizes 1 and 2 seem to cause issues, presumably we'd need to run for
  more iterations to get a decent GFLOP/s estimate.
- Collapsing the loop seems to have had a detrimental effect compared to
  vectorising the inner loop.

---

# Contiguous and non-contiguous memory layout

```
$ ./loop
The standard loop took 48743.9 microseconds to complete.
The vectorised loop took 9337.3 microseconds to complete.

$ ./loop2
The standard loop took 69643.1 microseconds to complete.
The vectorised loop took 42843.9 microseconds to complete.
```

The vectorised loop performs much quicker when the memory layout is contiguous
on my laptop.
