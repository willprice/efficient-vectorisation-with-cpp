CPPFLAGS ?= -O2
CPPFLAGS += --std=c++14 -Iinclude -fopenmp-simd

.PHONY: all
all: test loop reduction function collapse loop2 array_of_structs struct_of_arrays
