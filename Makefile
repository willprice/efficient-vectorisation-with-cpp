CPPFLAGS ?= -O3
CPPFLAGS += --std=c++14 -Iinclude -O2 -ffast-math -fopenmp-simd


.PHONY: all
all: test loop
