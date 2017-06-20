#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>


#define BUCKET_SIZE 1 << 6

/* AVG Meaning calculation for file */
int main(int argc, char *argv[]) {
    struct stat s;
    uint64_t sum = 0;
    uint64_t count = 0;
    uint32_t i;
    int64_t avg, entropy;
    uint32_t accuracy = 100000; // 5 numbers after point
    int64_t fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        printf("Can't open file: %s\n", argv[1]);
        return 1;
    }

    /* Get the size of the file. */
    fstat (fd, & s);
    uint32_t file_size = s.st_size;

    uint32_t *input_data = (uint32_t *) mmap (0, file_size, PROT_READ, MAP_PRIVATE, fd, 0);

    for (i = 0; i < file_size/sizeof(uint32_t); i++) {
        sum += input_data[i];
        count++;
    }

    // close(file);

    avg = sum / count;
    entropy = avg*accuracy/(1 << 31); // 0-100000
    printf("AVG Meaning: %li ~= Entropy lvl: %li\n", avg, entropy);
}
