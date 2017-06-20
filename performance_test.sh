#!/bin/bash -e

cd "$(dirname $0)"

# Gen test data
{
    dd if=/dev/urandom bs=64K count=1
    dd if=/dev/zero    bs=64K count=1
} > indata.bin

{
    echo "---"
    echo avg_meaning_entropy
    START=$(date +%s)
    for i in {1..10000}; do
        ./avg_meaning_entropy ./indata.bin > /dev/null
    done
    STOP=$(date +%s)
    echo $(($STOP-$START))s
}

{
    echo "---"
    echo shannon_entropy
    START=$(date +%s)
    for i in {1..10000}; do
        ./shannon_entropy ./indata.bin > /dev/null
    done
    STOP=$(date +%s)
    echo $(($STOP-$START))s
}

{
    echo "---"
    echo shannon_int_entropy
    START=$(date +%s)
    for i in {1..10000}; do
        ./shannon_int_entropy ./indata.bin > /dev/null
    done
    STOP=$(date +%s)
    echo $(($STOP-$START))s
}

{
    echo "---"
    echo gzip -f -k -3 ./indata.bin
    START=$(date +%s)
    for i in {1..10000}; do
        gzip -f -k -3 ./indata.bin > /dev/null
    done
    STOP=$(date +%s)
    echo $(($STOP-$START))s
}

{
    echo "---"
    echo lzop -f -k -3 ./indata.bin
    START=$(date +%s)
    for i in {1..10000}; do
        lzop -f -k -3 ./indata.bin > /dev/null
    done
    STOP=$(date +%s)
    echo $(($STOP-$START))s
}
