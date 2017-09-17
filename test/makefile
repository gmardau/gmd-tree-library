CPP = g++
CPPFLAGS = -Wall -Wextra -Werror -pedantic-errors -std=c++17 -O2
TREE = -include ../tree

all: main tests

main:
	$(CPP) $(CPPFLAGS) main.cpp -c -o main.o

tests: $(eval SRC = $(shell find ./ -type f -name '*.cpp' ! -name main.cpp ! -name manual.cpp))
	$(CPP) $(CPPFLAGS) $(TREE) $(SRC) main.o -o test

manual: manual.cpp
	$(CPP) $(CPPFLAGS) $(TREE) manual.cpp -o manual

clean:
	rm -f main.o test manual
