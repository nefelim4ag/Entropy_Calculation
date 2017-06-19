# Entropy_Calculation
Proof of concept, calculation entropy of data stream

I've writen C/C++ realization of:
- AVG meaning entropy
- Shannon entropy
- Shannon entropy only with integer logic (for kernel)

algorithm_tests - implementation what calculate entropy for above algo

log2_generator - can generate precalculated values of log2 (and function)
with assumption that arg will be left shifted by 16 bit
and return value of log2_lshift16() will be left shifted by 6 bit
All that shifts used for avoid of using floating point in calculation

log2_lshift16.h - store precalculated function (log2(arg << 24)) << 6

This code does not accept args, just try reading data from: ./indata.bin

performance_test.sh - stupid but simple methods to compare algorithms

```
# Compile:
~$ make

# Example of genering test data
~$ dd if=/dev/urandom bs=4M count=1 of=indata.bin

# Run performance test script
./performance_test.sh
```
