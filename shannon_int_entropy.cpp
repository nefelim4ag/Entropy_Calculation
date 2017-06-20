#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
/* Precalculated log2 realization */
#include "log2_lshift16.h"

#define LOG2_ARG_SHIFT (1 << 16)
#define LOG2_RET_SHIFT (1 << 6)

/* Shannon integer entropy calculation */
#define BUCKET_SIZE (1 << 8)
int main() {
    uint64_t count = 0;
    uint64_t entropy = 0;

    /*
     * For small data set it's possible to change size of word
     * input data size <= 65536 byte - uint16_t
     * input data size <= 4294967296 byte - uint32_t
     */
    uint32_t *array = (uint32_t *) calloc(BUCKET_SIZE, sizeof(uint32_t));
    std::ifstream infile("indata.bin");

    if (infile.is_open()) {
        std::cout << "Open file: ./indata.bin\n";
    } else {
        std::cout << "Can't open file: ./indata.bin\n";
        return 1;
    }

    /* Try add compiller some space for vectorization */
    while (!infile.eof()) {
        uint8_t B4[8];
        infile.read((char *) &B4, sizeof(B4));
        for (uint8_t i = 0; i < sizeof(B4); i++) {
            array[B4[i]]++;
        }
        count+=sizeof(B4);
    }


    for (uint16_t i = 0; i < BUCKET_SIZE; i++) {
        if (array[i]) {
            uint64_t val = array[i];
            val = val*LOG2_ARG_SHIFT/count;
            entropy += -val*log2_lshift16(val);
        }
    }

    double entropy_d = entropy*100.0/LOG2_ARG_SHIFT/(8*LOG2_RET_SHIFT);
    printf("Schanon int entropy: %lu/512 ~= %f%%\n",
        entropy/LOG2_ARG_SHIFT, entropy_d);
    free(array);
}
