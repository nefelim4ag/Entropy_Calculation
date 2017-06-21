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
# I think that 90% of time losts in initialization process
./performance_test.sh

Test good compressible data: 128k
avg mean:       8s
shannon float:  11s
shannon integ:  12s
heuristic:      8s
gzip -ck -3 ./indata.bin:       18s
lzop -ck -3 ./indata.bin:       14s
lzop -ck -1 ./indata.bin:       14s
- - - - -
Test half compressible data: 128k
avg mean:       9s
shannon float:  11s
shannon integ:  11s
heuristic:      8s
gzip -ck -3 ./indata.bin:       36s
lzop -ck -3 ./indata.bin:       14s
lzop -ck -1 ./indata.bin:       14s
- - - - -
Test bad compressible data: 128k
avg mean:       8s
shannon float:  10s
shannon integ:  10s
heuristic:      8s
gzip -ck -3 ./indata.bin:       62s
lzop -ck -3 ./indata.bin:       14s
lzop -ck -1 ./indata.bin:       14s
- - - - -
Test good compressible data: 8k
avg mean:       7s
shannon float:  9s
shannon integ:  8s
heuristic:      7s
gzip -ck -3 ./indata.bin:       8s
lzop -ck -3 ./indata.bin:       13s
lzop -ck -1 ./indata.bin:       13s
- - - - -
Test half compressible data: 8k
avg mean:       7s
shannon float:  9s
shannon integ:  8s
heuristic:      8s
gzip -ck -3 ./indata.bin:       9s
lzop -ck -3 ./indata.bin:       13s
lzop -ck -1 ./indata.bin:       13s
- - - - -
Test bad compressible data: 8k
avg mean:       8s
shannon float:  8s
shannon integ:  8s
heuristic:      8s
gzip -ck -3 ./indata.bin:       10s
lzop -ck -3 ./indata.bin:       12s
lzop -ck -1 ./indata.bin:       12s
```
