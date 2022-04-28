export CXXFLAGS=-std=c++14	-Wall -Wextra -Werror -O2

all: main display
ifeq ($(OS),Windows_NT)
	@g++ -o main.exe main.o ../lib/display.o ../lib/pdcurses.a $(CXXFLAGS)
else
	@g++ -o main main.o ../lib/display.o -lncurses $(CXXFLAGS)
endif

main: main.cpp 
	@g++ -c -o main.o main.cpp $(CXXFLAGS)

display: ../lib
	@cd ../lib && make -s
	
@PHONY: clean
clean:
ifeq ($(OS),Windows_NT)
	@-del /f main.exe main.o 2> nul
else
	@-rm -f main main.o
endif
	@cd ../lib && make -s clean
