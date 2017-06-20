CFLAGS=-O2 -Wall -Werror -lm
CC=gcc

default all: log2_generator avg_meaning_entropy shannon_entropy shannon_int_entropy

log2_generator: log2_generator.o
	$(CC) $(CFLAGS) -o log2_generator log2_generator.o log2_lshift16.o

log2_generator.o: log2_generator.c log2_lshift16.c
	$(CC) $(CFLAGS) -c log2_generator.c log2_lshift16.c


avg_meaning_entropy: avg_meaning_entropy.o
	$(CC) $(CFLAGS) -o avg_meaning_entropy avg_meaning_entropy.o

avg_meaning_entropy.o: avg_meaning_entropy.c
	$(CC) $(CFLAGS) -c avg_meaning_entropy.c


shannon_entropy: shannon_entropy.o
	$(CC) $(CFLAGS) -o shannon_entropy shannon_entropy.o

shannon_entropy.o: shannon_entropy.c
	$(CC) $(CFLAGS) -c shannon_entropy.c


shannon_int_entropy: shannon_int_entropy.o
	$(CC) $(CFLAGS) -o shannon_int_entropy shannon_int_entropy.o log2_lshift16.o

shannon_int_entropy.o: shannon_int_entropy.c log2_lshift16.c
	$(CC) $(CFLAGS) -c shannon_int_entropy.c log2_lshift16.c

clean: ## Cleanup
	git clean -dfx

help: ## Show help
	@fgrep -h "##" $(MAKEFILE_LIST) | fgrep -v fgrep | sed -e 's/\\$$//' | sed -e 's/##/\t/'
