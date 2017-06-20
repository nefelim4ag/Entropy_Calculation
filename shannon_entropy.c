#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>

/* Shannon entropy calculation */
#define BUCKET_SIZE 1 << 8

int main(int argc, char *argv[]) {
    double entropy_sum = 0;
    double entropy_l;
    int64_t count = 0;
    uint32_t i = 0;
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
        for (i = 0; i < BUCKET_SIZE; i++)
            bucket[input_data[i]]++;
        count+=BUCKET_SIZE;
    }
    fclose(file);

    for (i = 0; i < BUCKET_SIZE; i++) {
        if (bucket[i]) {
            entropy_l = bucket[i];
            entropy_l = entropy_l/count;
            entropy_sum += -(entropy_l)*log2(entropy_l);
        }
    }
    free(bucket);

    printf("Schanon true entropy: %f/8 ~= %f%%\n",
        entropy_sum, entropy_sum*100/8);
}
