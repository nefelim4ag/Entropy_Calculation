#!/bin/bash

cd "$(dirname $0)"

# Gen test data
rnd_zero_100_0(){ dd if=/dev/urandom bs=128K count=1 2> /dev/null; }
rnd_zero_0_100(){ dd if=/dev/zero    bs=128K count=1 2> /dev/null; }
rnd_zero_50_50(){
    for i in {0..15}; do
        dd if=/dev/urandom bs=4K count=1 2> /dev/null
        dd if=/dev/zero    bs=4K count=1 2> /dev/null
    done
}

avg_mean_test(){
    echo -en "avg mean:\t"
    START=$(date +%s)
    for i in {1..10000}; do
        ./entropy_calc 1 ./indata.bin > /dev/null
    done
    STOP=$(date +%s)
    echo "$(($STOP-$START))s"
}

shannon_entropy(){
    echo -en "shannon float:\t"
    START=$(date +%s)
    for i in {1..10000}; do
        ./entropy_calc 2 ./indata.bin > /dev/null
    done
    STOP=$(date +%s)
    echo "$(($STOP-$START))s"
}

shannon_int_entropy(){
    echo -en "shannon integ:\t"
    START=$(date +%s)
    for i in {1..10000}; do
        ./entropy_calc 3 ./indata.bin > /dev/null
    done
    STOP=$(date +%s)
    echo "$(($STOP-$START))s"
}

shannon_int_entropy_heuristic(){
    echo -en "heuristic:\t"
    START=$(date +%s)
    for i in {1..10000}; do
        ./entropy_calc 4 ./indata.bin > /dev/null
    done
    STOP=$(date +%s)
    echo "$(($STOP-$START))s"
}

gzip_lvl(){
    echo -en "gzip -ck -$1 ./indata.bin:\t"
    START=$(date +%s)
    for i in {1..10000}; do
        gzip -c -k -$1 ./indata.bin > /dev/null
    done
    STOP=$(date +%s)
    echo "$(($STOP-$START))s"
}

lzo_lvl(){
    echo -en "lzop -ck -$1 ./indata.bin:\t"
    START=$(date +%s)
    for i in {1..10000}; do
        lzop -ck -$1 ./indata.bin > /dev/null
    done
    STOP=$(date +%s)
    echo "$(($STOP-$START))s"
}

echo "Test good compressible data"
rnd_zero_0_100 > indata.bin
avg_mean_test
shannon_entropy
shannon_int_entropy
shannon_int_entropy_heuristic
gzip_lvl 3
lzo_lvl 3
lzo_lvl 1

echo "- - - - -"

echo "Test half compressible data"
rnd_zero_50_50 > indata.bin
avg_mean_test
shannon_entropy
shannon_int_entropy
shannon_int_entropy_heuristic
gzip_lvl 3
lzo_lvl 3
lzo_lvl 1

echo "- - - - -"

echo "Test bad compressible data"
rnd_zero_100_0 > indata.bin
avg_mean_test
shannon_entropy
shannon_int_entropy
shannon_int_entropy_heuristic
gzip_lvl 3
lzo_lvl 3
lzo_lvl 1
