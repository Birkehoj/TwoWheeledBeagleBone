#!/bin/bash

if [[ ! -d build ]]; then
	mkdir -p build
fi

cd build

cmake .. -DCMAKE_TOOLCHAIN_FILE=arm-toolchain.cmake -DCMAKE_BUILD_TYPE=Debug
cpucount=`nproc`
cmake --build . -- -j${cpucount}
