CPPFLAGS ?= -O2  
CPPFLAGS += --std=c++14 -Iinclude -ffast-math -fopenmp-simd


.PHONY: all
all: test loop
