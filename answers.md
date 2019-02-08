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
