#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <time.h>

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

#define MAX_READ_SIZE 131072

void help(char *self_name){
	printf("%s <mode_num 1-4> <file_path>\n", self_name);
	printf("\t0 - for init time measurement, do nothing\n");
	printf("\t1 - avg_mean\n");
	printf("\t2 - shannon float\n");
	printf("\t3 - shannon integer\n");
	printf("\t4 - heuristic\n");
}

int main(int argc, char *argv[]) {
	struct stat file_stat;
	uint64_t file_size;
	uint8_t *input_data;
	uint8_t mode;
	int64_t fd;
	uint64_t black_hole = 0;
	uint64_t *_input_data;
	enum compress_advice ret;
	clock_t start, end;

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

	int prot = PROT_READ|PROT_NONE;
	int map_flags =  MAP_SHARED;
	input_data = (uint8_t *) mmap (0, file_size, prot, map_flags, fd, 0);

	start = clock()*1000000/CLOCKS_PER_SEC;

	switch (mode) {
	case INIT_PROF:
		_input_data = (uint64_t *) input_data;
		for (uint64_t i = 0; i < file_size/8; i++)
			black_hole += _input_data[i];
		break;;
	case AVG_MEAN:
		for (uint64_t i = 0; i < file_size; i+=MAX_READ_SIZE) {
			if (file_size <= MAX_READ_SIZE) {
				avg_mean(input_data, file_size);
			} else {
				if (file_size - i > MAX_READ_SIZE)
					avg_mean(&input_data[i], MAX_READ_SIZE);
				else
					avg_mean(&input_data[i], file_size - i);
			}
		}
		break;;
	case SHANNON_F:
		for (uint64_t i = 0; i < file_size; i+=MAX_READ_SIZE) {
			if (file_size - i >= MAX_READ_SIZE)
				shannon_f(&input_data[i], MAX_READ_SIZE);
			else
				shannon_f(&input_data[i], file_size - i);
		}
		break;;
	case SHANNON_I:
		for (uint64_t i = 0; i < file_size; i+=MAX_READ_SIZE) {
			if (file_size <= MAX_READ_SIZE) {
				shannon_i(input_data, file_size);
			} else {
				if (file_size - i > MAX_READ_SIZE)
					shannon_i(&input_data[i], MAX_READ_SIZE);
				else
					shannon_i(&input_data[i], file_size - i);
			}
		}
		break;;
	case HEURISTIC:
		for (uint64_t i = 0; i < file_size; i+=MAX_READ_SIZE) {
			if (file_size <= MAX_READ_SIZE) {
				ret = heuristic(input_data, file_size);
			} else {
				if (file_size - i > MAX_READ_SIZE)
					ret = heuristic(&input_data[i], MAX_READ_SIZE);
				else
					ret = heuristic(&input_data[i], file_size - i);
			}
			switch (ret) {
			case COMPRESS_NONE:
				printf("Not Compress\n");
				break;;
			case COMPRESS_COST_EASY:
				printf("Compress cost: EASY\n");
				break;;
			case COMPRESS_COST_MEDIUM:
				printf("Compress cost: MEDIUM\n");
				break;;
			case COMPRESS_COST_HARD:
				printf("Compress cost: HARD\n");
				break;;
			}
		}
	break;;
	default:
		help(argv[0]);
		return 1;
	}

	end = clock()*1000000/CLOCKS_PER_SEC;
	printf("Perf: %lu ms ~ %fMB/s\n", (end - start)/1000, file_size*1.0/(end - start));

	return 0;
}
