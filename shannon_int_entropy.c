#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

/* Precalculated log2 realization */
#include "log2_lshift16.h"

#define LOG2_ARG_SHIFT (1 << 16)
#define LOG2_RET_SHIFT (1 << 6)

/* Shannon integer entropy calculation */
#define BUCKET_SIZE (1 << 8)
int main(int argc, char *argv[]) {
    uint64_t count = 0;
    uint64_t entropy_sum = 0;
    uint64_t entropy_l;
    double entropy_d;
    uint32_t i;
    /* Expected that: 4096 <= input data size <= 4294967296 */
    uint32_t *bucket = (uint32_t *) calloc(BUCKET_SIZE, sizeof(uint32_t));
    /* Try add compiller some space for vectorization */
    uint8_t input_data[BUCKET_SIZE];

    FILE *file = fopen(argv[1], "rb");
    if (!file) {
        printf("Can't open file: %s\n", argv[1]);
        return 1;
    }


    while (!feof(file)) {
        fread(&input_data, BUCKET_SIZE, 1, file);
        for (uint16_t i = 0; i < BUCKET_SIZE; i++)
            bucket[input_data[i]]++;
        count+=BUCKET_SIZE;
    }
    fclose(file);


    for (i = 0; i < BUCKET_SIZE; i++) {
        if (bucket[i]) {
            entropy_l = bucket[i];
            entropy_l = entropy_l*LOG2_ARG_SHIFT/count;
            entropy_sum += -entropy_l*log2_lshift16(entropy_l);
        }
    }
    free(bucket);

    entropy_d = entropy_sum*100.0/LOG2_ARG_SHIFT/(8*LOG2_RET_SHIFT);
    printf("Schanon int entropy: %lu/512 ~= %f%%\n",
        entropy_sum/LOG2_ARG_SHIFT, entropy_d);
}
