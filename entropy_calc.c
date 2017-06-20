#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>

/* Entropy calculation methods */
#include "avg_mean.h"
#include "shannon_f.h"

#include "log2_lshift16.h"

#define AVG_MEAN  1
#define SHANNON_F 2
#define SHANNON_I 3
#define HEURISTIC 4

int main(int argc, char *argv[]) {
    struct stat file_stat;
    /* Expected that: 4096 <= input data size <= 4294967296 */
    uint64_t max_input_size = (1 << 31);
    uint64_t file_size;
    uint8_t *input_data;
    uint8_t mode;
    int64_t fd;

    /* Check num of args */
    if (argc != 3) {
        printf("%s <mode_num 1-4> <file_path>", argv[0]);
        return 1;
    }

    mode = atoi(argv[1]);
    fd = open(argv[2], O_RDONLY);
    if (fd == -1) {
        printf("Can't open file: %s\n", argv[1]);
        return 1;
    }

    /* Get the size of the file. */
    fstat (fd, &file_stat);
    file_size = file_stat.st_size;

    if (file_size >= max_input_size) {
        printf("Max supported input file size 4G");
        return 1;
    }

    input_data = (uint8_t *) mmap (0, file_size, PROT_READ, MAP_PRIVATE, fd, 0);

    switch (mode) {
    case AVG_MEAN:
        avg_mean(input_data, file_size);
        break;;
    case SHANNON_F:
        shannon_f(input_data, file_size);
        break;;
    case SHANNON_I:
        break;;
    case HEURISTIC:
        break;;
    default:
        printf("%s <mode_num 1-4> <file_path>", argv[0]);
        return 1;
    }

    return 0;
}
