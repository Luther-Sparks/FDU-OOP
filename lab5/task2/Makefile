export CXXFLAGS=-std=c++14	-Wall -Wextra -Werror -O2
export LDFLAGS=-lncurses

all: main.o display.o bird.o
	@echo "Linking..."
	@g++ -o main.exe main.o bird.o ../display/display.o $(CXXFLAGS) $(LDFLAGS)

main.o: main.cpp 
	@echo "Compiling main.cpp"
	@g++ -c -o main.o main.cpp $(CXXFLAGS)

display.o: ../display
	@echo "Compiling display..."
	@cd ../display && make

bird.o: bird.cpp bird.h
	@echo "Compiling bird.cpp"
	@g++ -c -o bird.o bird.cpp $(CXXFLAGS)


#clean
@PHONY: clean
clean:
	rm -f main.exe main.o bird.o
	@cd ../display && make clean