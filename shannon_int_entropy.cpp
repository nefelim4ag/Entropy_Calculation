#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
/* Precalculated log2 realization */
#include "log2_lshift16.h"

/* Shannon integer entropy calculation */
int main() {
    int64_t count = 0;

    uint32_t array[256];
    for (uint32_t i = 0; i < 256; i++) array[i] = 0;

    std::ifstream infile("indata.bin");

    if (infile.is_open()) {
        std::cout << "Open file: ./indata.bin\n";
    } else {
        std::cout << "Can't open file: ./indata.bin\n";
        return 1;
    }

    while (!infile.eof()) {
        uint8_t B4[4];
        infile.read((char *) &B4, sizeof(B4));
        array[B4[0]]++;
        array[B4[1]]++;
        array[B4[2]]++;
        array[B4[3]]++;
        count+=4;
    }

    uint64_t entropy = 0;
    for (uint16_t i = 0; i < 256; i++) {
        if (array[i] == 0) continue;
        uint64_t val = array[i]*65536/count;
        entropy += -val*log2_lshift16(val);
    }
    double entropy_d = entropy;
    std::cout << "Schanon int entropy: " << entropy/65536 << "/128 == " << entropy_d*100/65536/128 << "%" << '\n';
}
