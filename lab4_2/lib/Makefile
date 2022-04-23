export CXXFLAGS=-std=c++17	-Wall -Wextra -Werror -O2
all: display audio
display:
	@g++ -c -o display.o display.cpp $(CXXFLAGS)
audio:
	@g++ -c -o audio.o audio.cpp $(CXXFLAGS)
@PHONY: clean
clean:
ifeq ($(OS),Windows_NT)
	@-del /f display.o audio.o 2> nul
else
	@-rm -f display.o audio.o
endif