#!/bin/bash -e

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
    echo -n "avg_meaning_entropy "
    START=$(date +%s)
    for i in {1..10000}; do
        ./avg_meaning_entropy ./indata.bin > /dev/null
    done
    STOP=$(date +%s)
    echo "$(($STOP-$START))s"
}

shannon_entropy(){
    echo -n "shannon_entropy "
    START=$(date +%s)
    for i in {1..10000}; do
        ./shannon_entropy ./indata.bin > /dev/null
    done
    STOP=$(date +%s)
    echo "$(($STOP-$START))s"
}

shannon_int_entropy(){
    echo -n "shannon_int_entropy "
    START=$(date +%s)
    for i in {1..10000}; do
        ./shannon_int_entropy ./indata.bin > /dev/null
    done
    STOP=$(date +%s)
    echo "$(($STOP-$START))s"
}

shannon_int_entropy_heuristic(){
    echo -n "shannon_int_entropy_heuristic "
    START=$(date +%s)
    for i in {1..10000}; do
        ./shannon_int_entropy_heuristic ./indata.bin > /dev/null
    done
    STOP=$(date +%s)
    echo "$(($STOP-$START))s"
}

gzip_lvl_3(){
    echo -n "gzip -f -k -3 ./indata.bin "
    START=$(date +%s)
    for i in {1..10000}; do
        gzip -c -f -k -3 ./indata.bin > /dev/null
    done
    STOP=$(date +%s)
    echo "$(($STOP-$START))s"
}

lzo_lvl_3(){
    echo -n "lzop -f -k -3 ./indata.bin "
    START=$(date +%s)
    for i in {1..10000}; do
        lzop -c -k -3 ./indata.bin > /dev/null
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
gzip_lvl_3
lzo_lvl_3

echo "- - - - -"

echo "Test half compressible data"
rnd_zero_50_50 > indata.bin
avg_mean_test
shannon_entropy
shannon_int_entropy
shannon_int_entropy_heuristic
gzip_lvl_3
lzo_lvl_3

echo "- - - - -"

echo "Test bad compressible data"
rnd_zero_100_0 > indata.bin
avg_mean_test
shannon_entropy
shannon_int_entropy
shannon_int_entropy_heuristic
gzip_lvl_3
lzo_lvl_3
