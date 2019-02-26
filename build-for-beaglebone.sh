#!/bin/bash

build_path="build/arm"

if [[ ! -d $build_path ]]; then
	mkdir -p $build_path
fi

cd $build_path

cmake .. -DCMAKE_TOOLCHAIN_FILE=arm-toolchain.cmake -DCMAKE_BUILD_TYPE=Debug
cpucount=`nproc`
cmake --build . -- -j${cpucount}
#-grecord-gcc-switches
