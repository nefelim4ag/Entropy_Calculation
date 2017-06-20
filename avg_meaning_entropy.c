#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>


#define BUCKET_SIZE 1 << 6

/* AVG Meaning calculation for file */
int main(int argc, char *argv[]) {
    int64_t sum = 0;
    uint64_t count = 0;
    uint32_t i;
    int64_t avg, entropy;
    int32_t accuracy = 100000; // 5 numbers after point
    uint32_t input_data[BUCKET_SIZE];

    FILE *file = fopen(argv[1], "rb");

    if (!file) {
        printf("Can't open file: %s\n", argv[1]);
        return 1;
    }

    while (!feof(file)) {
        fread(&input_data, BUCKET_SIZE, 4, file);
        for (i = 0; i < BUCKET_SIZE; i++)
            sum+=input_data[i];
        count+=BUCKET_SIZE;
    }
    fclose(file);

    avg = sum / count;
    entropy = accuracy - abs(accuracy - avg*accuracy/(1 << 31)); // 0-100000
    printf("AVG Meaning: %li ~= Entropy lvl: %li\n", avg, entropy);
}
