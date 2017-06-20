#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

/* AVG Meaning calculation for file */
int main(int argc, char *argv[]) {
    int64_t sum = 0;
    uint64_t count = 0;
    int64_t avg, entropy;
    FILE *file = fopen(argv[1], "rb");

    if (!file) {
        printf("Can't open file: %s\n", argv[1]);
        return 1;
    }

    uint32_t B4[4];
    while (!feof(file)) {
        fread(&B4, sizeof(B4), 1, file);
        for (uint8_t i = 0; i < sizeof(B4)/sizeof(uint32_t); i++) {
            sum+=B4[i];
        }
        count+=4;
    }
    fclose(file);

    avg = sum / count;
    entropy = 100000 - abs(100000 - avg*100000/2147483648); // 0-100000
    printf("AVG Meaning: %li ~= Entropy lvl: %li\n", avg, entropy);
}
