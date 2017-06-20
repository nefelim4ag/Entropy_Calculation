#!/bin/bash -e

cd "$(dirname $0)"

# Gen test data
{
    dd if=/dev/urandom bs=64K count=1
    dd if=/dev/zero    bs=64K count=1
} > indata.bin

echo "---"
echo avg_meaning_entropy
date
for i in {1..10000}; do
    ./avg_meaning_entropy ./indata.bin > /dev/null
done
date

echo "---"
echo shannon_entropy
date
for i in {1..10000}; do
    ./shannon_entropy ./indata.bin > /dev/null
done
date

echo "---"
echo shannon_int_entropy
date
for i in {1..10000}; do
    ./shannon_int_entropy ./indata.bin > /dev/null
done
date

echo "---"
echo gzip -f -k -3 ./indata.bin
date
for i in {1..10000}; do
    gzip -f -k -3 ./indata.bin > /dev/null
done
date

echo "---"
echo lzop -f -k -3 ./indata.bin
date
for i in {1..10000}; do
    lzop -f -k -3 ./indata.bin > /dev/null
done
date
