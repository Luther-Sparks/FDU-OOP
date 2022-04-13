CXXFLAGS=-std=c++14	-Wall -Wextra -Werror -O2
main:
ifeq ($(OS),Windows_NT)
	@g++ -o main.exe main.cpp ../lib/pdcurses.a $(CXXFLAGS) 
	@./main.exe
endif
#clean
@PHONY: clean
clean:
ifeq ($(OS),Windows_NT)
	@-del /f main.exe main.o 2> nul
else
	@-rm -f main.exe main.o
endif
	@cd ../lib && make clean

