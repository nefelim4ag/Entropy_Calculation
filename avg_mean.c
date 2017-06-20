#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "avg_mean.h"

int avg_mean(uint8_t *input_data, uint64_t bytes_len) {
    uint64_t sum = 0;
    uint64_t count = bytes_len/sizeof(uint32_t);
    uint64_t avg;
    int32_t accuracy = 100000;
    int32_t entropy;
    uint32_t *_input_data = (uint32_t *) input_data;

    for (uint32_t i = 0; i < count; i++) {
        sum += _input_data[i];
    }

    avg = sum*accuracy/count;
    entropy = avg/2147483648; // avg vs expected avg for random data
    entropy = accuracy - abs(accuracy - entropy);
    printf("AVG Meaning: %lu ~= Entropy lvl: %i\n", avg, entropy);

    return 0;
}
