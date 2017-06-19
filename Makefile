PREFIX ?= /

CPPFLAGS=-O2 -Wall -Werror
CXX=g++

default all: log2_generator avg_meaning_entropy shannon_entropy shannon_int_entropy algorypthm_tests

log2_generator: log2_generator.o
	$(CXX) $(CPPFLAGS) -o log2_generator log2_generator.o

log2_generator.o: log2_generator.cpp log2_lshift16.h
	$(CXX) $(CPPFLAGS) -c log2_generator.cpp


avg_meaning_entropy: avg_meaning_entropy.o
	$(CXX) $(CPPFLAGS) -o avg_meaning_entropy avg_meaning_entropy.o

avg_meaning_entropy.o: avg_meaning_entropy.cpp
	$(CXX) $(CPPFLAGS) -c avg_meaning_entropy.cpp


shannon_entropy: shannon_entropy.o
	$(CXX) $(CPPFLAGS) -o shannon_entropy shannon_entropy.o

shannon_entropy.o: avg_meaning_entropy.cpp
	$(CXX) $(CPPFLAGS) -c shannon_entropy.cpp


shannon_int_entropy: shannon_int_entropy.o
	$(CXX) $(CPPFLAGS) -o shannon_int_entropy shannon_int_entropy.o

shannon_int_entropy.o: shannon_int_entropy.cpp log2_lshift16.h
	$(CXX) $(CPPFLAGS) -c shannon_int_entropy.cpp


algorypthm_tests: algorypthm_tests.o
	$(CXX) $(CPPFLAGS) -o algorypthm_tests algorypthm_tests.o

algorypthm_tests.o: algorypthm_tests.cpp log2_lshift16.h
	$(CXX) $(CPPFLAGS) -c algorypthm_tests.cpp

clean: ## Cleanup
	git clean -dfx

help: ## Show help
	@fgrep -h "##" $(MAKEFILE_LIST) | fgrep -v fgrep | sed -e 's/\\$$//' | sed -e 's/##/\t/'
