CFLAGS=-O2 -Wall -Werror -lm
CC=gcc

default all: log2_generator entropy_calc

log2_generator: log2_generator.o log2_lshift16.o
	$(CC) $(CFLAGS) -o log2_generator log2_generator.o log2_lshift16.o

log2_generator.o: log2_generator.c
	$(CC) $(CFLAGS) -c log2_generator.c


entropy_calc: entropy_calc.o avg_mean.o shannon_f.o shannon_i.o log2_lshift16.o heuristic.o sort.o
	$(CC) $(CFLAGS) -o entropy_calc entropy_calc.o avg_mean.o shannon_f.o shannon_i.o log2_lshift16.o heuristic.o sort.o

entropy_calc.o: entropy_calc.c
	$(CC) $(CFLAGS) -c entropy_calc.c

avg_mean.o: avg_mean.c
	$(CC) $(CFLAGS) -c avg_mean.c

shannon_f.o: shannon_f.c
	$(CC) $(CFLAGS) -c shannon_f.c

shannon_i.o: shannon_i.c
	$(CC) $(CFLAGS) -c shannon_i.c

log2_lshift16.o: log2_lshift16.c
	$(CC) $(CFLAGS) -c log2_lshift16.c

heuristic.o: heuristic.c
	$(CC) $(CFLAGS) -c heuristic.c

sort.o: sort.c
	$(CC) $(CFLAGS) -c sort.c

clean: ## Cleanup
	git clean -dfx

help: ## Show help
	@fgrep -h "##" $(MAKEFILE_LIST) | fgrep -v fgrep | sed -e 's/\\$$//' | sed -e 's/##/\t/'
