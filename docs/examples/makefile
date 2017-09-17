CPP = g++
CPPFLAGS = -Wall -Wextra -Werror -pedantic-errors -std=c++17
TREE = -include ../../tree
DIR = ./

all: $(patsubst %.cpp, %, $(shell find $(DIR) -type f -name '*.cpp'))
%: %.cpp
	$(CPP) $(CPPFLAGS) $(TREE) $< -o $@

clean: $(eval SRC = $(shell find $(DIR) -type f ! -name '*.cpp' ! -name makefile))
	$(if $(SRC), rm $(SRC))
