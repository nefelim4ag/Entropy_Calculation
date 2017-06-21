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
AVG Initialization time: 17018ms
avg mean:       3240ms
shannon float:  11537ms
shannon integ:  9933ms
heuristic:      2060ms
gzip -ck -3 /run/user/1000/test_data.bin:       19767ms
lzop -ck -3 /run/user/1000/test_data.bin:       12393ms
lzop -ck -1 /run/user/1000/test_data.bin:       13660ms
- - - - -
Test half compressible data: 128k
AVG Initialization time: 15820ms
avg mean:       3302ms
shannon float:  8680ms
shannon integ:  9659ms
heuristic:      3207ms
gzip -ck -3 /run/user/1000/test_data.bin:       57245ms
lzop -ck -3 /run/user/1000/test_data.bin:       14175ms
lzop -ck -1 /run/user/1000/test_data.bin:       15392ms
- - - - -
Test bad compressible data: 128k
AVG Initialization time: 16878ms
avg mean:       4410ms
shannon float:  7113ms
shannon integ:  6777ms
heuristic:      2162ms
gzip -ck -3 /run/user/1000/test_data.bin:       110578ms
lzop -ck -3 /run/user/1000/test_data.bin:       14238ms
lzop -ck -1 /run/user/1000/test_data.bin:       15332ms
- - - - -
Test good compressible data: 8k
AVG Initialization time: 17526ms
avg mean:       1683ms
shannon float:  5762ms
shannon integ:  2427ms
heuristic:      1858ms
gzip -ck -3 /run/user/1000/test_data.bin:       2745ms
lzop -ck -3 /run/user/1000/test_data.bin:       10221ms
lzop -ck -1 /run/user/1000/test_data.bin:       11960ms
- - - - -
Test half compressible data: 8k
AVG Initialization time: 17513ms
avg mean:       1853ms
shannon float:  1933ms
shannon integ:  2572ms
heuristic:      2571ms
gzip -ck -3 /run/user/1000/test_data.bin:       4167ms
lzop -ck -3 /run/user/1000/test_data.bin:       9502ms
lzop -ck -1 /run/user/1000/test_data.bin:       10923ms
- - - - -
Test bad compressible data: 8k
AVG Initialization time: 18164ms
avg mean:       -28ms
shannon float:  312ms
shannon integ:  1891ms
heuristic:      542ms
gzip -ck -3 /run/user/1000/test_data.bin:       6407ms
lzop -ck -3 /run/user/1000/test_data.bin:       9088ms
lzop -ck -1 /run/user/1000/test_data.bin:       10741ms
```
