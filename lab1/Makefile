#!/bin/bash

# Please enter your name and student ID down here
# Name:
STD_NAME := 
# Student ID:
STD_ID   := 
#Like this
# STD_NAME := 野兽先辈
# STD_ID   := 21307114514

UNAME := $(shell uname)
ifeq ($(UNAME), Windows_NT)
	TESTFILE_NAME := testFindKthStr.exe
else
	TESTFILE_NAME := testFindKthStr
endif

compile:
	-mkdir build
	cd build && cmake .. && make
	@echo "Done with make compile"

grade:
	g++ -Wall -Wextra -Werror -std=c++14 -o $(TESTFILE_NAME) testFindKthStr.cpp
	./$(TESTFILE_NAME)
	@echo "Done with make grade"

clean:
	rm -f $(TESTFILE_NAME)
	rm -r ./build
	@echo "Done with make clean"

all:compile grade
	@echo "Done with make all"

handin:
	-mkdir src
	-cp lab1_$(STD_NAME)_$(STD_ID).pdf findKthStr.cpp src/
	zip -r lab1_$(STD_NAME)_$(STD_ID).zip src/
	-rm -rf src/