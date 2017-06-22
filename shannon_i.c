#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "shannon_i.h"
/* Precalculated log2 realization */
#include "log2_lshift16.h"

/* Shannon full integer entropy calculation */
#define BUCKET_SIZE 1 << 8

int shannon_i(const uint8_t *input_data, const uint64_t bytes_len) {
    uint64_t count = bytes_len;
    uint64_t entropy_sum = 0;
    uint64_t entropy_max = 8*LOG2_RET_SHIFT;
    double entropy_perc;
    uint32_t i;
    uint32_t bucket[256];

    for (i = 0; i < bytes_len; i++)
        bucket[input_data[i]]++;

    for (i = 0; i < BUCKET_SIZE; i++) {
        if (bucket[i]) {
            uint64_t p = bucket[i];
            p = p*LOG2_ARG_SHIFT/count;
            entropy_sum += -p*log2_lshift16(p);
        }
    }

    entropy_sum = entropy_sum/LOG2_ARG_SHIFT;
    entropy_perc = entropy_sum*100.0/entropy_max;

    printf("Schanon int entropy: %lu/%lu ~= %f%%\n",
        entropy_sum, entropy_max, entropy_perc);

    return 0;
}
