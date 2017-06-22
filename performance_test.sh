#!/bin/bash
export INIT_TIME

# Gen test data
rnd_zero_100_0(){ dd if=/dev/urandom bs=$1 count=1 2> /dev/null; }
rnd_zero_0_100(){ dd if=/dev/zero    bs=$1 count=1 2> /dev/null; }
rnd_zero_50_50(){
    for i in $(seq 1 $1); do
        dd if=/dev/urandom bs=4K count=1 2> /dev/null
        dd if=/dev/zero    bs=4K count=1 2> /dev/null
    done
}

init_time(){
    START=$(($(date +%s%N)/1000/1000))
    for i in {1..20000}; do
        ./entropy_calc 0 /run/user/$UID/test_data.bin > /dev/null
    done
    STOP=$(($(date +%s%N)/1000/1000))
    echo "$(($STOP-$START))"
}

avg_mean_test(){
    echo -en "avg mean:\t"
    START=$(($(date +%s%N)/1000/1000))
    for i in {1..20000}; do
        ./entropy_calc 1 /run/user/$UID/test_data.bin > /dev/null
    done
    STOP=$(($(date +%s%N)/1000/1000))
    echo "$(($STOP-$INIT_TIME-$START))ms"
}

shannon_entropy(){
    echo -en "shannon float:\t"
    START=$(($(date +%s%N)/1000/1000))
    for i in {1..20000}; do
        ./entropy_calc 2 /run/user/$UID/test_data.bin > /dev/null
    done
    STOP=$(($(date +%s%N)/1000/1000))
    echo "$(($STOP-$INIT_TIME-$START))ms"
}

shannon_int_entropy(){
    echo -en "shannon integ:\t"
    START=$(($(date +%s%N)/1000/1000))
    for i in {1..20000}; do
        ./entropy_calc 3 /run/user/$UID/test_data.bin > /dev/null
    done
    STOP=$(($(date +%s%N)/1000/1000))
    echo "$(($STOP-$INIT_TIME-$START))ms"
}

shannon_int_entropy_heuristic(){
    echo -en "heuristic:\t"
    START=$(($(date +%s%N)/1000/1000))
    for i in {1..20000}; do
        ./entropy_calc 4 /run/user/$UID/test_data.bin > /dev/null
    done
    STOP=$(($(date +%s%N)/1000/1000))
    echo "$(($STOP-$INIT_TIME-$START))ms"
}

gzip_lvl(){
    echo -en "gzip -ck -$1 /run/user/$UID/test_data.bin:\t"
    START=$(($(date +%s%N)/1000/1000))
    for i in {1..20000}; do
        gzip -c -k -$1 /run/user/$UID/test_data.bin > /dev/null
    done
    STOP=$(($(date +%s%N)/1000/1000))
    echo "$(($STOP-$INIT_TIME-$START))ms"
}

lzo_lvl(){
    echo -en "lzop -ck -$1 /run/user/$UID/test_data.bin:\t"
    START=$(($(date +%s%N)/1000/1000))
    for i in {1..20000}; do
        lzop -ck -$1 /run/user/$UID/test_data.bin > /dev/null
    done
    STOP=$(($(date +%s%N)/1000/1000))
    echo "$(($STOP-$INIT_TIME-$START))ms"
}

normal_test(){
    avg_mean_test
    shannon_entropy
    shannon_int_entropy
    shannon_int_entropy_heuristic
    gzip_lvl 3
    lzo_lvl 1
}

echo "Test good compressible data: 128k"
rnd_zero_0_100 128K > /run/user/$UID/test_data.bin
INIT_TIME=$(init_time)
echo "AVG Initialization time: ${INIT_TIME}ms"
normal_test

echo "- - - - -"

echo "Test half compressible data: 128k"
rnd_zero_50_50 15 > /run/user/$UID/test_data.bin
INIT_TIME=$(init_time)
echo "AVG Initialization time: ${INIT_TIME}ms"
normal_test

echo "- - - - -"

echo "Test bad compressible data: 128k"
rnd_zero_100_0 128K > /run/user/$UID/test_data.bin
INIT_TIME=$(init_time)
echo "AVG Initialization time: ${INIT_TIME}ms"
normal_test

echo "- - - - -"

echo "Test good compressible data: 8k"
rnd_zero_0_100 8K > /run/user/$UID/test_data.bin
INIT_TIME=$(init_time)
echo "AVG Initialization time: ${INIT_TIME}ms"
normal_test

echo "- - - - -"

echo "Test half compressible data: 8k"
rnd_zero_50_50 1 > /run/user/$UID/test_data.bin
INIT_TIME=$(init_time)
echo "AVG Initialization time: ${INIT_TIME}ms"
normal_test

echo "- - - - -"

echo "Test bad compressible data: 8k"
rnd_zero_100_0 8K > /run/user/$UID/test_data.bin
INIT_TIME=$(init_time)
echo "AVG Initialization time: ${INIT_TIME}ms"
normal_test
