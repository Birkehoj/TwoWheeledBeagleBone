#!/bin/bash

build_path="build"

if [[ ! -d $build_path ]]; then
	mkdir -p $build_path
fi

cd $build_path

cmake .. -DCMAKE_TOOLCHAIN_FILE=arm-toolchain.cmake -DCMAKE_BUILD_TYPE=Debug -DTARGET_BEAGLEBONE=TRUE
cpucount=`nproc`
cmake --build . --clean-first -- -j${cpucount}
#-grecord-gcc-switches
