CFLAGS=-O2 -Wall -Werror -lm

default all: log2_generator entropy_calc

log2_generator.o: log2_generator.c
	$(CC) $(CFLAGS) -c $? -o $@

log2_lshift16.o: log2_lshift16.c
	$(CC) $(CFLAGS) -c $? -o $@

entropy_calc.o: entropy_calc.c
	$(CC) $(CFLAGS) -c $? -o $@

avg_mean.o: avg_mean.c
	$(CC) $(CFLAGS) -c $? -o $@

shannon_f.o: shannon_f.c
	$(CC) $(CFLAGS) -c $? -o $@

shannon_i.o: shannon_i.c
	$(CC) $(CFLAGS) -c $? -o $@

heuristic.o: heuristic.c
	$(CC) $(CFLAGS) -c $? -o $@

sort.o: sort.c
	$(CC) $(CFLAGS) -c $? -o $@

detect_zeroes.o: detect_zeroes.c
	$(CC) $(CFLAGS) -c $? -o $@

log2_generator: log2_generator.o log2_lshift16.o
	$(CC) $(CFLAGS) -o $@ $?

entropy_calc: entropy_calc.o avg_mean.o shannon_f.o shannon_i.o log2_lshift16.o heuristic.o sort.o detect_zeroes.o
	$(CC) $(CFLAGS) -o $@ $?


clean: ## Cleanup
	git clean -dfx

help: ## Show help
	@fgrep -h "##" $(MAKEFILE_LIST) | fgrep -v fgrep | sed -e 's/\\$$//' | sed -e 's/##/\t/'
