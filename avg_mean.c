#include <stdint.h>
#include <stdio.h>
#include "avg_mean.h"

int avg_mean(uint8_t *input_data, uint64_t bytes_len) {
    int64_t sum = 0;
    uint64_t count = 0;
    int64_t avg;
    int64_t accuracy = 100000;
    int64_t entropy;
    uint32_t i;
    uint32_t *_input_data = (uint32_t *) input_data;

    count = bytes_len/sizeof(uint32_t);
    for (i = 0; i < count; i++) {
        sum += _input_data[i];
    }

    avg = sum*accuracy/count;
    entropy = avg/2147483648; // 0-100000
    printf("AVG Meaning: %li ~= Entropy lvl: %li\n", avg, entropy);

    return 0;
}
