display:
	@g++ -c -o display.o display.cpp $(CXXFLAGS)
@PHONY: clean
clean:
ifeq ($(OS),Windows_NT)
	@del display.a display.o
else
	@rm -f display.o
endif