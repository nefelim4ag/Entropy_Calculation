#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "int_sqrt.h"
#include "heuristic.h"
/* Precalculated log2 realization */
#include "log2_lshift16.h"

/* For shannon full integer entropy calculation */
#define BUCKET_SIZE (1 << 8)

/* true - try compress, false - ignore */
bool heuristic(uint8_t *input_data, uint64_t bytes_len) {
    bool ret = false;
    uint32_t std_dev;
    uint32_t count = 0;
    uint16_t entropy_max = LOG2_RET_SHIFT*8;
    uint64_t entropy_sum = 0;
    uint32_t square_sum = 0;
    uint16_t symbset_size = 0;
    uint32_t avg = 0;
    uint32_t a, b;
    uint16_t *bucket = (uint16_t *) calloc(BUCKET_SIZE, sizeof(uint16_t));
    uint16_t offset_count = 128;

    /* Read small subset of data 2kb-4kb */
    for (a = 0; a < bytes_len; a+=bytes_len/offset_count) {
        for (b = 0; b < 16 && (a+b) < bytes_len; b++) {
            bucket[input_data[a+b]]++;
        }
    }

    /*
     * Count symbol types
     * Assume that for bad compressible data
     * After check 128 values from bucket
     * Code will find charset_size >= 64
     */
    for (a = 0; a < BUCKET_SIZE/2; a++) {
        if (bucket[a])
            symbset_size++;
    }

    /*
     * If set of symbols are small: 0-64 of 256
     * Entropy of data are low, so just go to compression
     */
    for (a = BUCKET_SIZE/2; a < BUCKET_SIZE && symbset_size < 64; a++) {
        if (bucket[a])
            symbset_size++;
    }

    if (symbset_size < 64) {
        ret = true;
        goto out;
    }

    /*
     * Compute Standard Deviation
     * For bad compressible data standard deviation
     * are tupicaly small 0-6
     */
    count = offset_count*16;
    avg = count/256;
    for (a = 0; a < BUCKET_SIZE; a++) {
        square_sum += (bucket[a]-avg)*(bucket[a]-avg);
    }

    std_dev = int_sqrt(square_sum/(count - 1));
    if (std_dev < 5) {
        ret = false;
        goto out;
    }

    /*
     * Okay, code fail to fast detect data type
     * Let's calculate entropy
     */
    for (a = 0; a < BUCKET_SIZE; a++) {
        if (bucket[a]) {
            uint64_t p = bucket[a];
            p = p*LOG2_ARG_SHIFT/count;
            entropy_sum += -p*log2_lshift16(p);
        }
    }

    /* Assume that acceptable compression ratio are 0.90 */
    entropy_sum = entropy_sum / LOG2_ARG_SHIFT;
    if (entropy_sum*100/entropy_max <= 90)
        ret = true;
out:
    free(bucket);
    return ret;
}
