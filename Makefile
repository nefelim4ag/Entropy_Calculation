PREFIX ?= /

CPPFLAGS=-O2 -Wall
CXX=g++

default all: log2_generator avg_meaning_entropy shannon_entropy shannon_int_entropy

log2_generator:
	$(CXX) $(CPPFLAGS) log2_generator.cpp -o log2_generator

avg_meaning_entropy:
	$(CXX) $(CPPFLAGS) avg_meaning_entropy.cpp -o avg_meaning_entropy

shannon_entropy:
	$(CXX) $(CPPFLAGS) shannon_entropy.cpp -o shannon_entropy

shannon_int_entropy:
	$(CXX) $(CPPFLAGS) shannon_int_entropy.cpp -o shannon_int_entropy

clean: ## Cleanup
	git clean -dfx

help: ## Show help
	@fgrep -h "##" $(MAKEFILE_LIST) | fgrep -v fgrep | sed -e 's/\\$$//' | sed -e 's/##/\t/'
