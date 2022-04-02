CXXFLAGS=-std=c++14	-Wall -Wextra -Werror -O2
LDFLAGS=-lncurses

all: main display
	@g++ -o main.exe main.o display.o $(CXXFLAGS) $(LDFLAGS)

main: main.cpp
	@g++ -c -o main.o main.cpp $(CXXFLAGS)

display: display.cpp display.h
	@g++ -c -o display.o display.cpp $(CXXFLAGS)
#clean
@PHONY: clean
clean:
	rm -f main.exe main.o display.o