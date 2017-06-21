#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "shannon_f.h"

/* Shannon entropy calculation */
#define BUCKET_SIZE 1 << 8

int shannon_f(uint8_t *input_data, uint64_t bytes_len) {
    double entropy_sum = 0;
    double entropy_max = 8;
    uint64_t count = bytes_len;
    uint32_t i = 0;
    uint32_t *bucket = (uint32_t *) calloc(BUCKET_SIZE, sizeof(uint32_t));

    for (i = 0; i < bytes_len; i++)
        bucket[input_data[i]]++;

    for (i = 0; i < BUCKET_SIZE; i++) {
        if (bucket[i]) {
            double p = bucket[i];
            p = p/count;
            entropy_sum += -(p)*log2(p);
        }
    }

    free(bucket);

    printf("Schanon entropy: %f/%f ~= %f%%\n",
        entropy_sum, entropy_max, entropy_sum*100/entropy_max);

    return 0;
}
