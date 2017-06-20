PREFIX ?= /

CPPFLAGS=-O2 -Wall -Werror
CXX=g++
CFLAGS=-O2 -Wall -Werror
CC=gcc

default all: log2_generator avg_meaning_entropy shannon_entropy shannon_int_entropy algorypthm_tests

log2_generator: log2_generator.o
	$(CXX) $(CPPFLAGS) -o log2_generator log2_generator.o

log2_generator.o: log2_generator.cpp log2_lshift16.h
	$(CXX) $(CPPFLAGS) -c log2_generator.cpp


avg_meaning_entropy: avg_meaning_entropy.o
	$(CC) $(CFLAGS) -o avg_meaning_entropy avg_meaning_entropy.o

avg_meaning_entropy.o: avg_meaning_entropy.c
	$(CC) $(CFLAGS) -c avg_meaning_entropy.c


shannon_entropy: shannon_entropy.o
	$(CXX) $(CPPFLAGS) -o shannon_entropy shannon_entropy.o

shannon_entropy.o: shannon_entropy.c
	$(CXX) $(CPPFLAGS) -c shannon_entropy.c


shannon_int_entropy: shannon_int_entropy.o
	$(CC) $(CFLAGS) -o shannon_int_entropy shannon_int_entropy.o

shannon_int_entropy.o: shannon_int_entropy.c log2_lshift16.h
	$(CC) $(CFLAGS) -c shannon_int_entropy.c


algorypthm_tests: algorypthm_tests.o
	$(CXX) $(CPPFLAGS) -o algorypthm_tests algorypthm_tests.o

algorypthm_tests.o: algorypthm_tests.c log2_lshift16.h
	$(CXX) $(CPPFLAGS) -c algorypthm_tests.c

clean: ## Cleanup
	git clean -dfx

help: ## Show help
	@fgrep -h "##" $(MAKEFILE_LIST) | fgrep -v fgrep | sed -e 's/\\$$//' | sed -e 's/##/\t/'
