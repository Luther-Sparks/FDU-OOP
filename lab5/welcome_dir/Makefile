CXXFLAGS=-std=c++14	-Wall -Wextra -Werror -O2 -I C:\mingw64\include
LDFLAGS=-LC:\mingw64\lib -l:pdcurses.a
main:
	@g++ -o main.exe main.cpp $(CXXFLAGS) $(LDFLAGS)
	@./main.exe
#clean
@PHONY: clean
clean:
	rm -f main.exe

