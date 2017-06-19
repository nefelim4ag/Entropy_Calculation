# Entropy_Calculation
Proof of concept, calculation entropy of data stream

I've writen C/C++ realization of:
- AVG meaning entropy
- Shannon entropy
- Shannon entropy only with integer logic (for kernel)

```
# Compile:
~$ for file in ./*.cpp; g++ -O3 $file -o $(basename $file .cpp).bin
# Example of genering test data
~$ dd if=/dev/urandom bs=4M count=1 of=indata.bin
```
