#!/bin/bash
## clean CMake temporary files

cd .. # go to root of project

find . -iname "CMakeCache.txt" | xargs rm
find . -iname "CMakeFiles" | xargs rm -r
find . -iname "cmake_install.cmake" | xargs rm
