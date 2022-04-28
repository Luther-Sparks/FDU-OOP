export CXXFLAGS=-std=c++17	-Wall -Wextra -Werror -O2
all: display audio
display:
	@g++ -c -o display.o display.cpp $(CXXFLAGS)
audio:
ifeq ($(OS),Windows_NT)
	@g++ -c -o audio.o audio.cpp $(CXXFLAGS) -lwinmm
else
	@g++ -c -o audio.o audio.cpp $(CXXFLAGS)
endif
@PHONY: clean
clean:
ifeq ($(OS),Windows_NT)
	@-del /f display.o audio.o 2> nul
else
	@-rm -f display.o audio.o
endif