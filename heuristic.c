#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "heuristic.h"
/* Precalculated log2 realization */
#include "log2_lshift16.h"

/* Shannon full integer entropy calculation */
#define BUCKET_SIZE 1 << 8

int heuristic(uint8_t *input_data, uint64_t bytes_len) {
    uint64_t count = 0;
    uint64_t entropy_sum = 0;
    uint64_t entropy_l;
    double entropy_d;
    uint16_t coreset_size = 0;
    uint32_t a, b;
    uint32_t *bucket = (uint32_t *) calloc(BUCKET_SIZE, sizeof(uint32_t));

    /* Read small subset of data ~2kb */
    for (a = 0; a < bytes_len; a+=bytes_len/128) {
        for (b = 0; b < 16; b++)
            bucket[input_data[a+b]]++;
    }

    for (a = 0; a < BUCKET_SIZE; a++)
        count += bucket[a];

    for (a = 0; a < BUCKET_SIZE; a++)
        if (bucket[a])
            coreset_size++;

    if (coreset_size > 200) {
        printf("Data are bad compressible\n");
        exit(1);
    }

    if (coreset_size < 50) {
        printf("Data compressible\n");
        exit(0);
    }

    for (a = 0; a < BUCKET_SIZE; a++) {
        if (bucket[a]) {
            entropy_l = bucket[a];
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
