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
AVG Initialization time: 16357ms
avg mean:       1970ms
shannon float:  9678ms
shannon integ:  9581ms
heuristic:      1455ms
gzip -ck -3 /run/user/1000/test_data.bin:       19347ms
lzop -ck -3 /run/user/1000/test_data.bin:       11514ms
lzop -ck -1 /run/user/1000/test_data.bin:       13051ms
- - - - -
Test half compressible data: 128k
AVG Initialization time: 16601ms
avg mean:       1763ms
shannon float:  6749ms
shannon integ:  6769ms
heuristic:      2012ms
gzip -ck -3 /run/user/1000/test_data.bin:       54036ms
lzop -ck -3 /run/user/1000/test_data.bin:       11396ms
lzop -ck -1 /run/user/1000/test_data.bin:       13472ms
- - - - -
Test bad compressible data: 128k
AVG Initialization time: 16551ms
avg mean:       1752ms
shannon float:  4598ms
shannon integ:  4782ms
heuristic:      1348ms
gzip -ck -3 /run/user/1000/test_data.bin:       104797ms
lzop -ck -3 /run/user/1000/test_data.bin:       11593ms
lzop -ck -1 /run/user/1000/test_data.bin:       13076ms
- - - - -
Test good compressible data: 8k
AVG Initialization time: 16365ms
avg mean:       1300ms
shannon float:  1879ms
shannon integ:  1617ms
heuristic:      1329ms
gzip -ck -3 /run/user/1000/test_data.bin:       2005ms
lzop -ck -3 /run/user/1000/test_data.bin:       9334ms
lzop -ck -1 /run/user/1000/test_data.bin:       10123ms
- - - - -
Test half compressible data: 8k
AVG Initialization time: 16008ms
avg mean:       1318ms
shannon float:  2336ms
shannon integ:  2734ms
heuristic:      2215ms
gzip -ck -3 /run/user/1000/test_data.bin:       5073ms
lzop -ck -3 /run/user/1000/test_data.bin:       9359ms
lzop -ck -1 /run/user/1000/test_data.bin:       10509ms
- - - - -
Test bad compressible data: 8k
AVG Initialization time: 16152ms
avg mean:       1295ms
shannon float:  2283ms
shannon integ:  2011ms
heuristic:      1974ms
gzip -ck -3 /run/user/1000/test_data.bin:       5905ms
lzop -ck -3 /run/user/1000/test_data.bin:       9232ms
lzop -ck -1 /run/user/1000/test_data.bin:       10643ms
```
