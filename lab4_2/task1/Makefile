export CXXFLAGS=-std=c++14	-Wall -Wextra -Werror -O2

all: main.o lib.o bird.o
ifeq ($(OS),Windows_NT)
	@g++ -o main.exe main.o bird.o ../lib/display.o ../lib/audio.o ../lib/pdcurses.a $(CXXFLAGS) -lwinmm
else
	@g++ -o main main.o bird.o ../lib/display.o ../lib/audio.o -lncurses $(CXXFLAGS)
endif

stop:
ifneq ($(OS),Windows_NT)
	@echo "Stop the music"
	@pkill afplay || true
endif

main.o: main.cpp 
	@echo "Compiling main.cpp"
	@g++ -c -o main.o main.cpp $(CXXFLAGS)

lib.o:
	@echo "Compiling lib..."
	@cd ../lib && make -s


bird.o: bird.cpp bird.h
	@echo "Compiling bird.cpp"
	@g++ -c -o bird.o bird.cpp $(CXXFLAGS)

@PHONY: clean
clean:
ifeq ($(OS),Windows_NT)
	@-del /f main.exe main.o bird.o log.txt 2> nul
else
	@-rm -f main main.o bird.o log.txt
endif
	@cd ../lib && make -s clean
	@cd ../game && make -s clean