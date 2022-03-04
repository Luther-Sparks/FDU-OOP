#!/bin/bash

# Please enter your name and student ID down here
# Name:
STD_NAME := 123
# Student ID:
STD_ID   := 123
#Like this
# STD_NAME := 野兽先辈
# STD_ID   := 21307114514

ifeq ($(OS), Windows_NT)
	TESTFILE_NAME := testFindKthStr.exe
	RM := del
	CP := copy
	CMAKE_GENERATOR := -G "MinGW Makefiles"

handin:
	-mkdir src
	$(CP) lab1_$(STD_NAME)_$(STD_ID).pdf src
	$(CP) findKthStr.cpp src

clean:
	-$(RM) $(TESTFILE_NAME)
	@echo Done with make clean
	@echo on Windows you should delete directory '\build' manually

else
	TESTFILE_NAME := testFindKthStr
	RM := rm
	CP := cp
	CMAKE_GENERATOR := 

handin:
	-mkdir src
	$(CP) lab1_$(STD_NAME)_$(STD_ID).pdf src
	$(CP) findKthStr.cpp src
	zip -r lab1_$(STD_NAME)_$(STD_ID).zip src
	$(RM) -rf src
clean:
	-$(RM) -f $(TESTFILE_NAME)
	-$(RM) -r build/
	@echo "Done with make clean"

endif

compile:
	-mkdir build
	cd build && cmake .. $(CMAKE_GENERATOR) && make
	@echo "Done with make compile"

grade:
	g++ -Wall -Wextra -Werror -std=c++14 -o $(TESTFILE_NAME) testFindKthStr.cpp
	./$(TESTFILE_NAME)
	@echo "Done with make grade"



all:compile grade
	@echo "Done with make all"
