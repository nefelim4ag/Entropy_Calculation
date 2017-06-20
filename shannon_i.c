#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "shannon_i.h"
/* Precalculated log2 realization */
#include "log2_lshift16.h"

/* Shannon full integer entropy calculation */
#define BUCKET_SIZE 1 << 8

int shannon_i(uint8_t *input_data, uint64_t bytes_len) {
    uint64_t count = 0;
    uint64_t entropy_sum = 0;
    uint64_t entropy_l;
    double entropy_d;
    uint32_t i;
    /* Expected that: 4096 <= input data size <= 4294967296 */
    uint32_t *bucket = (uint32_t *) calloc(BUCKET_SIZE, sizeof(uint32_t));

    for (i = 0; i < bytes_len; i++)
        bucket[input_data[i]]++;

    for (i = 0; i < BUCKET_SIZE; i++)
        count += bucket[i];

    for (i = 0; i < BUCKET_SIZE; i++) {
        if (bucket[i]) {
            entropy_l = bucket[i];
            entropy_l = entropy_l*LOG2_ARG_SHIFT/count;
            entropy_sum += -entropy_l*log2_lshift16(entropy_l);
        }
    }
    free(bucket);

    entropy_d = entropy_sum*100.0/LOG2_ARG_SHIFT/(8*LOG2_RET_SHIFT);
    printf("Schanon int entropy: %lu/512 ~= %f%%\n",
        entropy_sum/LOG2_ARG_SHIFT, entropy_d);

    return 0;
}
