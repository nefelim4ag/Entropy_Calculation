# Entropy_Calculation
Proof of concept, calculation entropy of data stream

I've writen C/C++ realization of:
- AVG meaning entropy
- Shannon entropy
- Shannon entropy only with integer logic (for kernel)
- Heuristic (Mix of several methods)

log2_generator - can generate precalculated values of log2 (and function)
with assumption that arg will be left shifted by 16 bit
and return value of log2_lshift16() will be left shifted by 6 bit
All that shifts used for avoid of using floating point in calculation

log2_lshift16.h - header
log2_lshift16.c - store precalculated function (log2(arg << 24)) << 6

Values are precalculated only for:
```
## Increasing of that did not adding much impact on accuracy
1/131072 ... 131072/131072
```

performance_test.sh - stupid but simple methods to compare algorithms

```
###
# Compile:
~$ make

###
# Example of test
~$ dd if=/dev/urandom bs=4M count=1 of=indata.bin
~$ ./entropy_calc 3 ./indata.bin
Schanon int entropy: 510/512 ~= 99.660975%

###
# Run performance test script
./performance_test.sh

Test good compressible data
avg mean:       8s
shannon float:  12s
shannon integ:  12s
heuristic:      8s
gzip -ck -3 ./indata.bin:       17s
lzop -ck -3 ./indata.bin:       13s
- - - - -
Test half compressible data
avg mean:       8s
shannon float:  12s
shannon integ:  11s
heuristic:      8s
gzip -ck -3 ./indata.bin:       38s
lzop -ck -3 ./indata.bin:       15s
- - - - -
Test bad compressible data
avg mean:       8s
shannon float:  10s
shannon integ:  10s
heuristic:      8s
gzip -ck -3 ./indata.bin:       61s
lzop -ck -3 ./indata.bin:       13s
```
