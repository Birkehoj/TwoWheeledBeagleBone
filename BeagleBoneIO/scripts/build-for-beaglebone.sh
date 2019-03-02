#!/bin/bash

build_path="build/Debug/gcc-arm"

cd .. # go to root of project

if [[ ! -d $build_path ]]; then
	mkdir -p $build_path
fi

cmake  -B$build_path -H. -DCMAKE_TOOLCHAIN_FILE=cmake/arm-toolchain.cmake -DCMAKE_BUILD_TYPE=Debug

cpucount=`nproc`
cmake --build $build_path -- -j${cpucount}
#-grecord-gcc-switches
