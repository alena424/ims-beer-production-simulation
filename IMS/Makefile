
CC		= g++
FLAGS	= -std=c++11 -Wall -Wextra -Werror -g -pedantic -O2

.PHONY: clean build experiments run archive

build:	brewery brewery2 brewery3 brewery4 brewery5

brewery: main.o
	$(CC) $(FLAGS) -o $@ $^ -l simlib

main.o: main.cpp main.hpp
	$(CC) $(FLAGS) -c $<

brewery2: mainTanky.o
	$(CC) $(FLAGS) -o $@ $^ -l simlib

mainTanky.o: mainTanky.cpp mainTanky.hpp
	$(CC) $(FLAGS) -c $<

brewery3: mainSmeny.o
	$(CC) $(FLAGS) -o $@ $^ -l simlib

mainSmeny.o: mainSmeny.cpp mainSmeny.hpp
	$(CC) $(FLAGS) -c $<

brewery4: mainVareni.o
	$(CC) $(FLAGS) -o $@ $^ -l simlib

mainVareni.o: mainVareni.cpp mainVareni.hpp
	$(CC) $(FLAGS) -c $<

brewery5: mainPomer.o
	$(CC) $(FLAGS) -o $@ $^ -l simlib

mainPomer.o: mainPomer.cpp mainPomer.hpp
	$(CC) $(FLAGS) -c $<


clean:
	rm -f main.o brewery main.o brewery2 mainTanky.o brewery3 mainSmeny.o brewery4 mainVareni.o brewery5 mainPomer.o
