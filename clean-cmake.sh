#!/bin/bash
## clean CMake temporary files

find . -iname "CMakeCache.txt" | xargs rm
find . -iname "CMakeFiles" | xargs rm -r
find . -iname "cmake_install.cmake" | xargs rm
