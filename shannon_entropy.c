#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>

/* Shannon entropy calculation */
#define BUCKET_SIZE 1 << 8

int main(int argc, char *argv[]) {
    int64_t count = 0;
    double entropy = 0;
    FILE *file;

    /*
     * For small data set it's possible to change size of word
     * input data size <= 65536 byte - uint16_t
     * input data size <= 4294967296 byte - uint32_t
     */
    uint32_t *array = (uint32_t *) calloc(BUCKET_SIZE, sizeof(uint32_t));

    file = fopen(argv[1], "rb");

    if (!file) {
        printf("Can't open file: %s\n", argv[1]);
        return 1;
    }

    /* Try add compiller some space for vectorization */
    while (!feof(file)) {
        uint8_t B4[8];
        fread(&B4, sizeof(B4), 1, file);
        for (uint8_t i = 0; i < sizeof(B4); i++) {
            array[B4[i]]++;
        }
        count+=sizeof(B4);
    }
    fclose(file);

    for (uint16_t i = 0; i < BUCKET_SIZE; i++) {
        if (array[i]) {
            double val = array[i];
            val = val/count;
            entropy += -(val)*log2(val);
        }
    }

    printf("Schanon true entropy: %f/8 ~= %f%%\n", entropy, entropy*100/8);
    free(array);
}
