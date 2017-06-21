#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "heuristic.h"
/* Precalculated log2 realization */
#include "log2_lshift16.h"

/* For shannon full integer entropy calculation */
#define BUCKET_SIZE 1 << 8 // 256 counters

/* true - try compress, false - ignore */
bool heuristic(uint8_t *input_data, uint64_t bytes_len) {
    bool ret = false;
    uint32_t count = 0;
    uint64_t entropy_sum = 0;
    uint16_t charset_size = 0;
    uint32_t a, b;
    uint64_t rand = (uint64_t) &input_data;
    uint16_t *bucket = (uint16_t *) calloc(BUCKET_SIZE, sizeof(uint16_t));
    uint16_t offset_count = 128+rand%128;

    /* Read small subset of data 2kb-4kb */
    for (a = 0; a < bytes_len; a+=bytes_len/offset_count) {
        for (b = 0; b < 16 && (a+b) < bytes_len; b++) {
            bucket[input_data[a+b]]++;
        }
    }

    for (a = 0; a < BUCKET_SIZE; a++) {
        count += bucket[a];
        if (bucket[a])
            charset_size++;
    }

    if (charset_size < 64) {
        ret = true;
        goto out;
    }

    for (a = 0; a < BUCKET_SIZE; a++) {
        if (bucket[a]) {
            uint64_t p = bucket[a];
            p = p*LOG2_ARG_SHIFT/count;
            entropy_sum += -p*log2_lshift16(p);
        }
    }

    /* 4kb/128kb ~ 3,5% of 512 ~ 18*/
    if (entropy_sum/LOG2_ARG_SHIFT < 512-18)
        ret = true;
out:
    free(bucket);
    return ret;
}
