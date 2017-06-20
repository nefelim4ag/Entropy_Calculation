#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <time.h>       /* time */
#include "log2_lshift16.h"

const uint32_t SIZE = 128*1024*8*4; // 4MB

#define LOG2_ARG_SHIFT (1 << 16)
#define LOG2_RET_SHIFT (1 << 6)
#define BUCKET_SIZE (1 << 8)

int main(){
    srand (time(NULL));
    uint8_t PAGE[SIZE];

    // Gen test data
    uint32_t *P4B = (uint32_t *) PAGE;
    for (uint32_t i = 0; i < SIZE/4; i++) {
        P4B[i]=rand()*rand();
    }

    for (uint32_t i = 0; i < SIZE/4; i++) {
        if (rand()%32 == 256) P4B[i]=32;
    }

    { // AVG Meaning calculation
        int64_t sum = 0;
        int64_t avg;
        int64_t entropy;

        uint32_t *P4B = (uint32_t *) PAGE;
        for (uint32_t i = 0; i < SIZE/4; i++) {
            sum+=P4B[i];
        }

        avg = sum / (SIZE/4);
        entropy = 100000 - abs(100000 - avg*100000/2147483648); // 0-100000
        printf("AVG Meaning: %li ~= Entropy lvl: %li\n", avg, entropy);
    }
    { // Shannon entropy calculation
        uint8_t *P1B = (uint8_t *) PAGE;
        uint64_t *array = (uint64_t *) calloc(BUCKET_SIZE, sizeof(uint64_t));

        for (uint32_t i = 0; i < SIZE; i++)
            array[P1B[i]]++;

        {
            double entropy = 0;
            for (uint16_t i = 0; i < BUCKET_SIZE; i++) {
                if (array[i]) {
                    double val = array[i]*1.0/SIZE;
                    entropy += -(val)*log2(val);
                }
            }
            printf("Schanon true entropy: %f/8 ~= %f%%\n", entropy, entropy*100/8);
        }
        { // Shannon integer entropy calculation
            uint64_t entropy = 0;
            for (uint16_t i = 0; i < BUCKET_SIZE; i++) {
                if (array[i]) {
                    uint64_t val = array[i];
                    val = val*LOG2_ARG_SHIFT/SIZE;
                    entropy += -val*log2_lshift16(val);
                }
            }
            double entropy_d = entropy*100.0/LOG2_ARG_SHIFT/(8*LOG2_RET_SHIFT);
            printf("Schanon int entropy: %lu/512 ~= %f%%\n",
                entropy/LOG2_ARG_SHIFT, entropy_d);
        }
        free(array);
    }
}
