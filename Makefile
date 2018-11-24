
CC		= g++
FLAGS	= -std=c++11 -Wall -Wextra -Werror -g -pedantic -O2

.PHONY: clean build experiments run archive

build:	brewery

brewery: main.o
	$(CC) $(FLAGS) -o $@ $^ -l simlib

main.o: main.cpp main.hpp
	$(CC) $(FLAGS) -c $<

clean:
	rm -f main.o brewery main.o
