#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sort.h"
#include "heuristic.h"
/* Precalculated log2 realization */
#include "log2_lshift16.h"

/* For shannon full integer entropy calculation */
#define __BUCKET_SIZE (1 << 8)

struct __bucket_item {
	uint8_t  padding;
	uint8_t  symbol;
	uint16_t count;
};

/* For sorting */
static int32_t compare(const void *lhs, const void *rhs) {
	struct __bucket_item *l = (struct __bucket_item *)(lhs);
	struct __bucket_item *r = (struct __bucket_item *)(rhs);
	return r->count - l->count;
}


/*
 * For good compressible data
 * Charset size over sample
 * will be small < 64
 */
#define __SYMBSET_HIGH 64
static uint32_t __symbset_calc(const struct __bucket_item *bucket)
{
	uint32_t a = 0;
	uint32_t symbset_size = 0;

	for (; a < __SYMBSET_HIGH+1; a++) {
		if (bucket[a].count)
			symbset_size++;
	}

	if (symbset_size >= __SYMBSET_HIGH)
		return symbset_size;

	for (; a < __BUCKET_SIZE && symbset_size < __SYMBSET_HIGH; a++) {
		if (bucket[a].count)
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
#define __CORESET_LOW 50
#define __CORESET_HIGH 200
static uint32_t __coreset_calc(const struct __bucket_item *bucket,
	const uint32_t sum_threshold)
{
	uint32_t a = 0;
	uint32_t coreset_sum = 0;

	for (; a < __CORESET_LOW-1; a++)
		coreset_sum += bucket[a].count;

	if (coreset_sum > sum_threshold)
		return a;

	for (; a < __CORESET_HIGH+1 && bucket[a].count > 0; a++) {
		coreset_sum += bucket[a].count;
		if (coreset_sum > sum_threshold)
			break;
	}

	return a;
}

static uint64_t __entropy_perc(const struct __bucket_item *bucket,
	const uint32_t sample_size)
{
	uint32_t a, entropy_max = LOG2_RET_SHIFT*8;
	uint64_t p, entropy_sum = 0;

	for (a = 0; a < __BUCKET_SIZE && bucket[a].count > 0; a++) {
		p = bucket[a].count;
		p = p*LOG2_ARG_SHIFT/sample_size;
		entropy_sum += -p*log2_lshift16(p);
	}

	entropy_sum = entropy_sum / LOG2_ARG_SHIFT;
	return entropy_sum*100/entropy_max;
}

/* Pair distance from random distribution */
static uint32_t __rnd_dist(const struct __bucket_item *bucket,
	const uint32_t coreset_size, const uint8_t *sample, uint32_t sample_size)
{
	uint32_t a, b;
	uint8_t pair_a[2], pair_b[2];
	uint16_t *pair_c;
	uint32_t pairs_count;
	uint64_t sum = 0;
	uint64_t buf1, buf2;
	for (a = 0; a < coreset_size-1; a++) {
		pairs_count = 0;
		pair_a[0] = bucket[a].symbol;
		pair_a[1] = bucket[a+1].symbol;
		pair_b[1] = bucket[a].symbol;
		pair_b[0] = bucket[a+1].symbol;
		for (b = 0; b < sample_size-1; b++) {
			pair_c = (uint16_t *) &sample[b];
			if ( pair_c == (uint16_t *) pair_a)
				pairs_count++;
			else if (pair_c == (uint16_t *) pair_b)
				pairs_count++;
		}
		buf1 = bucket[a].count*bucket[a+1].count;
		buf1 = buf1*100000/(sample_size*sample_size);
		buf2 = pairs_count*2*100000;
		buf2 = pairs_count/sample_size;
		sum += (buf1 - buf2)*(buf1 - buf2);
	}

	return sum >> 11;
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
 *                   > 200 - data will be bad compressible, return
 *      in general this looks like data compression ratio 0.2 - 0.8
 * 4. Compute shannon entropy
 *    - shannon entropy count of bytes and can't count pairs & entropy_calc
 *      so assume:
 *        - usage of entropy can lead to false negative
 *          so for prevent that (in bad) case it's useful to "count" pairs
 *        - entropy are not to high < 70% easy compressible, return
 *        - entropy are high < 90%, try count pairs,
 *          if there is any noticeable amount, compression are possible, return
 *        - entropy are high > 90%, try count pairs,
 *          if there is noticeable amount, compression are possible, return
 */

#define READ_SIZE 16
#define __ENTROPY_LVL_MED 70
#define __ENTROPY_LVL_HIGH 90
static enum compress_advice ___heuristic(const uint8_t *sample,
	uint32_t sample_size)
{
	enum compress_advice ret = COMPRESS_COST_UNKNOWN;
	uint32_t a;
	uint64_t coreset_size, entropy_lvl;
	struct __bucket_item *bucket;

	bucket = (struct __bucket_item *) calloc(sizeof(struct __bucket_item),
		__BUCKET_SIZE);

	if (!bucket)
		goto out;

	for (a = 0; a < sample_size; a++)
		bucket[sample[a]].count++;

	a = __symbset_calc(bucket);
	if (a < __SYMBSET_HIGH) {
		ret = COMPRESS_COST_EASY;
		goto out;
	}

	/* Preset symbols, 0 - elemnt already set */
	for (a = 1; a < __BUCKET_SIZE; a++)
		bucket[a].symbol = a;

	/* Sort in reverse order */
	sort(bucket, __BUCKET_SIZE, sizeof(uint32_t), &compare, NULL);

	coreset_size = __coreset_calc(bucket, sample_size*90/100);

	if (coreset_size < __CORESET_LOW) {
		ret = COMPRESS_COST_EASY;
		goto out;
	}

	if (coreset_size > __CORESET_HIGH) {
		ret = COMPRESS_NONE;
		goto out;
	}

	/*
	 * Okay, code can't fast detect data type
	 * Let's calculate entropy
	 */
	entropy_lvl = __entropy_perc(bucket, sample_size);
	if (entropy_lvl < __ENTROPY_LVL_MED) {
		ret = COMPRESS_COST_MEDIUM;
		goto out;
	} else {
		a = __rnd_dist(bucket, a, sample, sample_size);
		if (entropy_lvl < __ENTROPY_LVL_HIGH) {
			if (a > 0)
				ret = COMPRESS_COST_MEDIUM;
			else
				ret = COMPRESS_NONE;
		} else {
			if (a > 10)
				ret = COMPRESS_COST_HARD;
			else
				ret = COMPRESS_NONE;
		}
	}

out:
	if (bucket)
		free(bucket);
	return ret;
}

enum compress_advice heuristic(const uint8_t *input_data,
	const uint64_t bytes_len)
{
	enum compress_advice ret = COMPRESS_COST_UNKNOWN;
	uint32_t offset_count, shift, sample_size;
	uint32_t a, b;
	uint8_t *sample;

	/*
	 * In data: 128K  64K   32K   4K
	 * Sample:  4096b 3072b 2048b 1024b
	 * Avoid allocating array bigger then 4kb
	 */

	if (bytes_len >= 96*1024) {
		offset_count = 256;
	} else {
		offset_count = 64 + bytes_len/512;
	}

	shift = bytes_len/offset_count;
	sample_size = offset_count*READ_SIZE;

	/*
	 * speedup by copy data to sample array +30%
	 * I think it's because of memcpy speed and
	 * cpu cache hits
	 */
	sample = (uint8_t *) malloc(sample_size);
	if (!sample)
		goto out;


	/* Read small subset of data 1024b-4096b */
	a = 0;
	b = 0;
	while (a < (bytes_len-READ_SIZE) && b < sample_size) {
		memcpy(&sample[b], &input_data[a], READ_SIZE);
		a += shift;
		b += READ_SIZE;
	}

	ret = ___heuristic(sample, sample_size);

out:
	if (sample)
		free(sample);
	return ret;
}
