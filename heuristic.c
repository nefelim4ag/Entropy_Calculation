#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "int_sqrt.h"
#include "sort.h"
#include "heuristic.h"
/* Precalculated log2 realization */
#include "log2_lshift16.h"

/* For shannon full integer entropy calculation */
#define BUCKET_SIZE (1 << 8)


/*
 * Algorythm description
 * 1. Get random subset of data for fast computation
 * 2. Scan bucket for symbol set
 *    - sumbol set < 64 - data will be easy compressible, return
 * 3. Try compute coreset size (symbols count that use 90% of input data)
 *    - reverse sort bucket
 *    - sum cells until we reach 90% threshold,
 *      incriment coreset size each time
 *    - coreset_size < 50  - data will be easy compressible, return
 *      coreset_size > 200 - data will be bad compressible, return
 * 4. ...
 */
/* true - try compress, false - ignore */
bool heuristic(const uint8_t *input_data, const uint64_t bytes_len) {
    bool ret = false;
    uint32_t entropy_max = LOG2_RET_SHIFT*8;
    uint64_t entropy_sum = 0;
    uint32_t symbset_size = 0;
    uint32_t coreset_size = 0;
    uint32_t coreset_sum = 0;
    uint32_t a, b;
    uint32_t *bucket = (uint32_t *) calloc(BUCKET_SIZE, sizeof(uint32_t));
    uint32_t offset_count = 128;
    uint32_t read_size = 16;
    uint32_t count = offset_count*read_size;
    uint32_t coreset_threshold = count*90/100;

    /* Read small subset of data 2kb-4kb */
    for (a = 0; a < bytes_len; a+=bytes_len/offset_count) {
        for (b = 0; b < read_size && (a+b) < bytes_len; b++) {
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
     * Try calculate coreset size
     * i.e. how many symbols use 90% of input data
     * < 50 - good compressible data
     * > 200 - bad compressible data
     * For fast calculation bucket must be reverse sorted
     */

    /* Sort in reverse order */
    sort(bucket, BUCKET_SIZE, sizeof(uint32_t), &compare, NULL);

    for (a = 0; a < BUCKET_SIZE; a++) {
        coreset_sum += bucket[a];
        if (coreset_sum < coreset_threshold) {
            coreset_size++;
        } else {
            break;
        }
    }

    if (coreset_size < 50) {
        ret = true;
        goto out;
    }

    if (coreset_size > 200) {
        ret = false;
        goto out;
    }

    /*
     * Okay, code fail to fast detect data type
     * Let's calculate entropy
     */
    for (a = 0; a < BUCKET_SIZE && bucket[a] > 0; a++) {
        uint64_t p = bucket[a];
        p = p*LOG2_ARG_SHIFT/count;
        entropy_sum += -p*log2_lshift16(p);
    }

    /* Assume that acceptable compression ratio are 0.90 */
    entropy_sum = entropy_sum / LOG2_ARG_SHIFT;
    if (entropy_sum*100/entropy_max <= 90)
        ret = true;
out:
    free(bucket);
    return ret;
}
