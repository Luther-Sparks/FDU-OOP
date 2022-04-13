display:
	@g++ -c -o display.o display.cpp $(CXXFLAGS)
@PHONY: clean
clean:
ifeq ($(OS),Windows_NT)
	@-del /f display.o 2> nul
else
	@-rm -f display.o
endif