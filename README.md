# Entropy_Calculation
Proof of concept, calculation entropy of data stream

I've writen C realization of:
- AVG meaning entropy
- Shannon entropy
- Shannon entropy only with integer logic (for kernel)
- Heuristic (Mix of several methods)

log2_generator - can generate precalculated values of log2 (and function)
with assumption that arg will be left shifted by 16 bit
and return value of log2_lshift16() will be left shifted by 3 bit
All that shifts used for avoid of using floating point in calculation

Yes, it's possible to use integer version of log2 with
some changes in algorithms, but when accuracy will suck

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
# You can also run over big files like VM images, videos, etc
# (file cached in page cache)
~$ make && ./entropy_calc 4 ~/Public/W10x64.1703.iso | grep -iv  compress
make: Nothing to be done for 'default'.
Perf: 983 ms ~ 4325.186706MB/s


###
# Run performance test script
# Performance test will measure initialization time
# And remove it from run time of tests
# This may be inaccurate in some cases
# But this allow see speed difference
./performance_test.sh

Test good compressible data: 128k
AVG Initialization time: 16032ms
avg mean:       2082ms
shannon float:  9945ms
shannon integ:  11756ms
heuristic:      2048ms
gzip -ck -3 /run/user/1000/test_data.bin:       20164ms
lzop -ck -1 /run/user/1000/test_data.bin:       14133ms
- - - - -
Test half compressible data: 128k
AVG Initialization time: 16143ms
avg mean:       2458ms
shannon float:  7781ms
shannon integ:  7439ms
heuristic:      2737ms
gzip -ck -3 /run/user/1000/test_data.bin:       55353ms
lzop -ck -1 /run/user/1000/test_data.bin:       14174ms
- - - - -
Test bad compressible data: 128k
AVG Initialization time: 16313ms
avg mean:       2428ms
shannon float:  5864ms
shannon integ:  5448ms
heuristic:      2415ms
gzip -ck -3 /run/user/1000/test_data.bin:       105410ms
lzop -ck -1 /run/user/1000/test_data.bin:       14008ms
- - - - -
Test good compressible data: 8k
AVG Initialization time: 16226ms
avg mean:       1872ms
shannon float:  2341ms
shannon integ:  2210ms
heuristic:      1582ms
gzip -ck -3 /run/user/1000/test_data.bin:       1832ms
lzop -ck -1 /run/user/1000/test_data.bin:       11136ms
- - - - -
Test half compressible data: 8k
AVG Initialization time: 16709ms
avg mean:       1276ms
shannon float:  2146ms
shannon integ:  1801ms
heuristic:      1499ms
gzip -ck -3 /run/user/1000/test_data.bin:       4799ms
lzop -ck -1 /run/user/1000/test_data.bin:       10677ms
- - - - -
Test bad compressible data: 8k
AVG Initialization time: 16461ms
avg mean:       1437ms
shannon float:  2203ms
shannon integ:  1880ms
heuristic:      2050ms
gzip -ck -3 /run/user/1000/test_data.bin:       6084ms
lzop -ck -1 /run/user/1000/test_data.bin:       10987ms
```
