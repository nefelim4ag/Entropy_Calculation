#!/bin/bash -e

cd "$(dirname $0)"

{
    dd if=/dev/urandom bs=1M count=4
    dd if=/dev/zero bs=1M count=4
} > indata.bin

echo "---"
time  ./avg_meaning_entropy
echo "---"
time ./shannon_entropy
echo "---"
time ./shannon_int_entropy
echo "---"
for lvl in {1..9}; do
    echo gzip -f -k -$lvl indata.bin
    time gzip -f -k -$lvl indata.bin
    echo "---"
done

for lvl in {1..9}; do
    echo lzop -f -k -$lvl indata.bin
    time lzop -f -k -$lvl indata.bin
    echo "---"
done
