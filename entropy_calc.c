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
#include "shannon_i.h"
#include "heuristic.h"

#define INIT_PROF 0 // Just for get init time + file reading
#define AVG_MEAN  1
#define SHANNON_F 2
#define SHANNON_I 3
#define HEURISTIC 4

void help(char *self_name){
    printf("%s <mode_num 1-4> <file_path>\n", self_name);
    printf("\t1 - avg_mean\n");
    printf("\t2 - shannon float\n");
    printf("\t3 - shannon integer\n");
    printf("\t4 - heuristic\n");
}

int main(int argc, char *argv[]) {
    struct stat file_stat;
    /* Expected that: 4096 <= input data size <= 4294967296 */
    uint64_t max_input_size = 4294967296;
    uint64_t min_input_size = 2048;
    uint64_t file_size;
    uint8_t *input_data;
    uint8_t mode;
    int64_t fd;
    uint64_t black_hole = 0;
    uint64_t *_input_data;

    /* Check num of args */
    if (argc != 3) {
        help(argv[0]);
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
        printf("Max supported input file size 4G\n");
        return 1;
    }
    if (file_size < min_input_size) {
        printf("Max supported input file size 4G\n");
        return 1;
    }

    int prot = PROT_READ|PROT_NONE;
    int map_flags =  MAP_SHARED|MAP_POPULATE;
    input_data = (uint8_t *) mmap (0, file_size, prot, map_flags, fd, 0);
    _input_data = (uint64_t *) input_data;

    switch (mode) {
    case INIT_PROF:
        _input_data = (uint64_t *) input_data;
        for (uint32_t i = 0; i < file_size/8; i++)
            black_hole += _input_data[i];
        break;;
    case AVG_MEAN:
        avg_mean(input_data, file_size);
        break;;
    case SHANNON_F:
        shannon_f(input_data, file_size);
        break;;
    case SHANNON_I:
        shannon_i(input_data, file_size);
        break;;
    case HEURISTIC:
        if (heuristic(input_data, file_size)) {
            printf("Try compressible\n");
        } else {
            printf("Skip compressible\n");
        }
        break;;
    default:
        help(argv[0]);
        return 1;
    }

    return 0;
}
