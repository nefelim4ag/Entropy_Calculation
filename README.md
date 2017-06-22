# Entropy_Calculation
Proof of concept, calculation entropy of data stream

I've writen C/C++ realization of:
- AVG meaning entropy
- Shannon entropy
- Shannon entropy only with integer logic (for kernel)
- Heuristic (Mix of several methods)

log2_generator - can generate precalculated values of log2 (and function)
with assumption that arg will be left shifted by 16 bit
and return value of log2_lshift16() will be left shifted by 3 bit
All that shifts used for avoid of using floating point in calculation

log2_lshift16.h - header
log2_lshift16.c - store precalculated function (log2(arg << 24)) << 3

Values are precalculated only for:
```
## Increasing of that did not adding much impact on accuracy
1/131072 ... 131072/131072
```

P.S.
[I got some ideas from this doc](https://www.usenix.org/system/files/conference/fast13/fast13-final38.pdf)

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
# Performance test will measure initialization time
# And remove it from run time of tests
# This may be inaccurate in some cases
# But this allow see speed difference
./performance_test.sh

Test good compressible data: 128k
AVG Initialization time: 15967ms
avg mean:       1750ms
shannon float:  10217ms
shannon integ:  9932ms
heuristic:      1477ms
gzip -ck -3 /run/user/1000/test_data.bin:       20249ms
lzop -ck -1 /run/user/1000/test_data.bin:       13377ms
- - - - -
Test half compressible data: 128k
AVG Initialization time: 16207ms
avg mean:       2090ms
shannon float:  7386ms
shannon integ:  7249ms
heuristic:      1913ms
gzip -ck -3 /run/user/1000/test_data.bin:       55726ms
lzop -ck -1 /run/user/1000/test_data.bin:       13620ms
- - - - -
Test bad compressible data: 128k
AVG Initialization time: 16253ms
avg mean:       1836ms
shannon float:  5525ms
shannon integ:  5302ms
heuristic:      1932ms
gzip -ck -3 /run/user/1000/test_data.bin:       106353ms
lzop -ck -1 /run/user/1000/test_data.bin:       13600ms
- - - - -
Test good compressible data: 8k
AVG Initialization time: 16107ms
avg mean:       1195ms
shannon float:  1380ms
shannon integ:  2027ms
heuristic:      1202ms
gzip -ck -3 /run/user/1000/test_data.bin:       1778ms
lzop -ck -1 /run/user/1000/test_data.bin:       11224ms
- - - - -
Test half compressible data: 8k
AVG Initialization time: 15848ms
avg mean:       1946ms
shannon float:  2715ms
shannon integ:  3246ms
heuristic:      2739ms
gzip -ck -3 /run/user/1000/test_data.bin:       5702ms
lzop -ck -1 /run/user/1000/test_data.bin:       12483ms
- - - - -
Test bad compressible data: 8k
AVG Initialization time: 16722ms
avg mean:       1622ms
shannon float:  2407ms
shannon integ:  2003ms
heuristic:      1574ms
gzip -ck -3 /run/user/1000/test_data.bin:       6066ms
lzop -ck -1 /run/user/1000/test_data.bin:       11305ms
```
