export CXXFLAGS=-std=c++14	-Wall -Wextra -Werror -O2
export LDFLAGS=-lncurses

all: main display
	@echo "Linking..."
	@g++ -o main.exe main.o ../display/display.o $(CXXFLAGS) $(LDFLAGS)

main: main.cpp 
	@echo "Compiling main.cpp"
	@g++ -c -o main.o main.cpp $(CXXFLAGS)

display: ../display
	@echo "Compiling display..."
	@cd ../display && make
	
#clean
@PHONY: clean
clean:
	rm -f main.exe main.o
	@cd ../display && make clean