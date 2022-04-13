export CXXFLAGS=-std=c++14	-Wall -Wextra -Werror -O2

all: main.o display.o bird.o
ifeq ($(OS),Windows_NT)
	@g++ -o main.exe main.o bird.o ../lib/display.o ../lib/pdcurses.a $(CXXFLAGS)
else
	@g++ -o main main.o bird.o ../lib/display.o -lncurses $(CXXFLAGS)
endif

main.o: main.cpp 
	@echo "Compiling main.cpp"
	@g++ -c -o main.o main.cpp $(CXXFLAGS)

display.o:
	@echo "Compiling display..."
	@cd ../lib && make -s

bird.o: bird.cpp bird.h
	@echo "Compiling bird.cpp"
	@g++ -c -o bird.o bird.cpp $(CXXFLAGS)

@PHONY: clean
clean:
ifeq ($(OS),Windows_NT)
	@-del /f main.exe main.o bird.o 2> nul
else
	@-rm -f main main.o bird.o
endif
	@cd ../lib && make -s clean