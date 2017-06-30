#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "shannon_f.h"

/* Shannon entropy calculation */
#define BUCKET_SIZE 1 << 8

bool detect_zeroes(const uint8_t *input_data, const uint64_t bytes_len) {
        size_t a = 0;
	size_t zero = 0;

	for (; a < bytes_len; a += sizeof(size_t)) {
		if (memcmp(&zero, &input_data[a], sizeof(size_t)))
			return false;
	}

	return true;
}
