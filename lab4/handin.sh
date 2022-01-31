#!/bin/bash

mkdir src
cp *.cpp *.h CMakeLists.txt src/
zip -r lab4.zip src/
rm -rf src/