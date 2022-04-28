export CXXFLAGS=-std=c++17 -Wall -Wextra -Werror -O2

all: rectangle moving_rectangle border display

rectangle: display
	@g++ -c -o rectangle.o rectangle.cpp $(CXXFLAGS)

moving_rectangle: rectangle
	@g++ -c -o moving_rectangle.o movingRectangle.cpp $(CXXFLAGS)

border: rectangle
	@g++ -c -o border.o border.cpp $(CXXFLAGS)

display: ../lib
	@cd ../lib && make -s
	
@PHONY: clean
clean:
ifeq ($(OS),Windows_NT)
	@-del /f rectangle.o moving_rectangle.o border.o 2> nul
else
	@-rm -f rectangle.o moving_rectangle.o border.o
endif