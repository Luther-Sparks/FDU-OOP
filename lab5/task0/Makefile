export CXXFLAGS=-std=c++14	-Wall -Wextra -Werror -O2

all: main display
ifeq ($(OS),Windows_NT)
	@g++ -o main.exe main.o ../lib/display.o ../lib/pdcurses.a $(CXXFLAGS)
endif

main: main.cpp 
	@g++ -c -o main.o main.cpp $(CXXFLAGS)

display: ../lib
	@cd ../lib && make
	
#clean
@PHONY: clean
clean:
ifeq ($(OS),Windows_NT)
	@del main.exe main.o
else
	@rm -f main.exe main.o
endif
	@cd ../lib && make clean
