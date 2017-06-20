#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>

/* Precalculated log2 realization */
#include "log2_lshift16.h"

/* Shannon integer entropy calculation + some heuristic */
#define BUCKET_SIZE (1 << 8)
int main(int argc, char *argv[]) {
    struct stat s;
    uint64_t count = 0;
    uint64_t entropy_sum = 0;
    uint64_t entropy_l;
    double entropy_d;
    uint16_t coreset_size = 0;
    uint32_t i;
    /* Expected that: 4096 <= input data size <= 4294967296 */
    uint32_t file_size;
    uint32_t *bucket = (uint32_t *) calloc(BUCKET_SIZE, sizeof(uint32_t));
    uint8_t *input_data;
    int64_t fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        printf("Can't open file: %s\n", argv[1]);
        return 1;
    }

    /* Get the size of the file. */
    fstat (fd, & s);
    file_size = s.st_size;

    input_data = (uint8_t *) mmap (0, file_size, PROT_READ, MAP_PRIVATE, fd, 0);

    /* Read small subset of data ~2kb */
    for (i = 0; i < file_size; i+=file_size/128) {
        for (uint32_t i2 = 0; i2 < 16; i2++)
            bucket[input_data[i+i2]]++;
    }

    // close(fd);

    for (i = 0; i < BUCKET_SIZE; i++)
        count += bucket[i];

    for (i = 0; i < BUCKET_SIZE; i++)
        if (bucket[i])
            coreset_size++;

    if (coreset_size > 200) {
        printf("Data are bad compressible\n");
        exit(1);
    }

    if (coreset_size < 50) {
        printf("Data compressible\n");
        exit(0);
    }

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
