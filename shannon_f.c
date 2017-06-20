#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "shannon_f.h"

/* Shannon entropy calculation */
#define BUCKET_SIZE 1 << 8

int shannon_f(uint8_t *input_data, uint64_t bytes_len) {
    double entropy_sum = 0;
    double entropy_l;
    int64_t count = 0;
    uint32_t i = 0;
    uint32_t *bucket = (uint32_t *) calloc(BUCKET_SIZE, sizeof(uint32_t));

    for (i = 0; i < bytes_len; i++)
        bucket[input_data[i]]++;

    for (i = 0; i < BUCKET_SIZE; i++)
        count += bucket[i];

    for (i = 0; i < BUCKET_SIZE; i++) {
        if (bucket[i]) {
            entropy_l = bucket[i];
            entropy_l = entropy_l/count;
            entropy_sum += -(entropy_l)*log2(entropy_l);
        }
    }

    free(bucket);

    printf("Schanon true entropy: %f/8 ~= %f%%\n",
        entropy_sum, entropy_sum*100/8);

    return 0;
}
