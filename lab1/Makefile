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

handin:
	-mkdir src
	$(CP) lab1_$(STD_NAME)_$(STD_ID).pdf src
	$(CP) findKthStr.cpp src

else
	TESTFILE_NAME := testFindKthStr
	RM := rm
	CP := cp

handin:
	-mkdir src
	$(CP) lab1_$(STD_NAME)_$(STD_ID).pdf src
	$(CP) findKthStr.cpp src
	zip -r lab1_$(STD_NAME)_$(STD_ID).zip src
	$(RM) -rf src/

endif

compile:
	-mkdir build
	cd build && cmake .. -G "MinGW Makefiles" && make
	@echo "Done with make compile"

grade:
	g++ -Wall -Wextra -Werror -std=c++14 -o $(TESTFILE_NAME) testFindKthStr.cpp
	./$(TESTFILE_NAME)
	@echo "Done with make grade"

clean:
	-$(RM) -f $(TESTFILE_NAME)
	-$(RM) -r ./build
	@echo "Done with make clean"

all:compile grade
	@echo "Done with make all"