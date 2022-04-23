export CXXFLAGS=-std=c++17 -Wall -Wextra -Werror -O2

rectangle: display
	@g++ -c -o rectangle.o rectangle.cpp $(CXXFLAGS)

display: ../lib
	@cd ../lib && make -s
	
@PHONY: clean
clean:
ifeq ($(OS),Windows_NT)
	@-del /f rectangle.o 2> nul
else
	@-rm -f rectangle.o
endif