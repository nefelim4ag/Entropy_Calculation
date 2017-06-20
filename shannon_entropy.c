#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <math.h>

/* Shannon entropy calculation */
#define BUCKET_SIZE 1 << 8

int main(int argc, char *argv[]) {
    struct stat s;
    double entropy_sum = 0;
    double entropy_l;
    int64_t count = 0;
    uint32_t i = 0;
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

    for (i = 0; i < file_size; i++) {
        bucket[input_data[i]]++;
    }

    // close(fd);

    for (i = 0; i < BUCKET_SIZE; i++)
        count += bucket[i];

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
