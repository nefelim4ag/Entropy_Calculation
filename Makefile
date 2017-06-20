CFLAGS=-O2 -Wall -Werror -lm
CC=gcc

default all: log2_generator avg_meaning_entropy shannon_entropy shannon_int_entropy algorypthm_tests

log2_generator: log2_generator.o
	$(CC) $(CFLAGS) -o log2_generator log2_generator.o

log2_generator.o: log2_generator.c log2_lshift16.h
	$(CC) $(CFLAGS) -c log2_generator.c


avg_meaning_entropy: avg_meaning_entropy.o
	$(CC) $(CFLAGS) -o avg_meaning_entropy avg_meaning_entropy.o

avg_meaning_entropy.o: avg_meaning_entropy.c
	$(CC) $(CFLAGS) -c avg_meaning_entropy.c


shannon_entropy: shannon_entropy.o
	$(CC) $(CFLAGS) -o shannon_entropy shannon_entropy.o

shannon_entropy.o: shannon_entropy.c
	$(CC) $(CFLAGS) -c shannon_entropy.c


shannon_int_entropy: shannon_int_entropy.o
	$(CC) $(CFLAGS) -o shannon_int_entropy shannon_int_entropy.o

shannon_int_entropy.o: shannon_int_entropy.c log2_lshift16.h
	$(CC) $(CFLAGS) -c shannon_int_entropy.c


algorypthm_tests: algorypthm_tests.o
	$(CC) $(CFLAGS) -o algorypthm_tests algorypthm_tests.o

algorypthm_tests.o: algorypthm_tests.c log2_lshift16.h
	$(CC) $(CFLAGS) -c algorypthm_tests.c

clean: ## Cleanup
	git clean -dfx

help: ## Show help
	@fgrep -h "##" $(MAKEFILE_LIST) | fgrep -v fgrep | sed -e 's/\\$$//' | sed -e 's/##/\t/'
