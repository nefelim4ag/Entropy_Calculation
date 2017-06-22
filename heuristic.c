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
 * For good compressible data
 * Charset size over sample
 * will be small <= 64
 */
static int _symbset_calc(const uint32_t *bucket)
{
    uint32_t a;
    uint32_t symbset_size = 0;
    for (a = 0; a < BUCKET_SIZE && symbset_size <= 64; a++) {
        if (bucket[a])
            symbset_size++;
    }
    return symbset_size;
}


/*
 * Try calculate coreset size
 * i.e. how many symbols use 90% of input data
 * < 50 - good compressible data
 * > 200 - bad compressible data
 * For right & fast calculation bucket must be reverse sorted
 */
static int _coreset_calc(const uint32_t *bucket,
    const uint32_t sum_threshold)
{
    uint32_t a = 0;
    uint32_t coreset_sum = 0;

    for (a = 0; a < 201; a++) {
        coreset_sum += bucket[a];
        if (coreset_sum < sum_threshold)
            break;
    }

    return a;
}

static int _entropy_perc(const uint32_t *bucket, const uint32_t count)
{
    uint32_t a, p;
    uint32_t entropy_sum = 0;
    uint32_t entropy_max = LOG2_RET_SHIFT*8;

    /*
     * Okay, code fail to fast detect data type
     * Let's calculate entropy
     */
    for (a = 0; a < BUCKET_SIZE && bucket[a] > 0; a++) {
        p = bucket[a];
        p = p*LOG2_ARG_SHIFT/count;
        entropy_sum += -p*log2_lshift16(p);
    }

    /* Assume that acceptable compression ratio are 0.70 */
    entropy_sum = entropy_sum / LOG2_ARG_SHIFT;
    return entropy_sum*100/entropy_max;
}
/*
 * Algorithm description
 * 1. Get subset of data for fast computation
 * 2. Scan bucket for symbol set
 *    - symbol set < 64 - data will be easy compressible, return
 * 3. Try compute coreset size (symbols count that use 90% of input data)
 *    - reverse sort bucket
 *    - sum cells until we reach 90% threshold,
 *      incriment coreset size each time
 *    - coreset_size < 50  - data will be easy compressible, return
 *      coreset_size > 200 - data will be bad compressible, return
 * 4. Compute shannon entropy
 *      - shannon entropy count of bytes and can't count pairs & entropy_calc
 *        so it's a average info per byte values
 *        so assume if entropy are not to high < 70%
 *        some compression algorithm can compress that data
 * 5. return decision
 */

#define READ_SIZE 16

/* true - compress, false - ignore */
bool heuristic(const uint8_t *input_data, const uint64_t bytes_len)
{
    uint32_t a, b;
    uint32_t bucket[256];
    uint32_t offset_count = 64 + bytes_len/4096;
    uint32_t shift = bytes_len/offset_count;
    uint32_t count = offset_count*READ_SIZE;
    uint32_t entropy_perc;
    uint32_t coreset_sum_threshold = count*90/100;

    for (a = 0; a < BUCKET_SIZE; a++)
        bucket[a] = 0;

    /* Read small subset of data 1536b-2048b */
    for (a = 0; a < (bytes_len-READ_SIZE); a += shift) {
        for (b = 0; b < READ_SIZE; b++) {
            bucket[input_data[a+b]]++;
        }
    }

    a = _symbset_calc(bucket);
    if (a < 64)
        return true;

    /* Sort in reverse order */
    sort(bucket, BUCKET_SIZE, sizeof(uint32_t), &compare, NULL);

    a = _coreset_calc(bucket, coreset_sum_threshold);

    if (a < 50)
        return true;

    if (a > 200)
        return false;

    entropy_perc = _entropy_perc(bucket, count);
    if (entropy_perc <= 70)
        return true;
    return false;
}
