#!/bin/bash

if [[ ! -d build ]]; then
	mkdir -p build
fi

cd build

# Hack to target arm
#export CC=/usr/bin/arm-linux-gnueabi-gcc-8
#export CXX=/usr/bin/arm-linux-gnueabi-g++-8
# end of hack
cmake .. -DCMAKE_TOOLCHAIN_FILE=arm-toolchain.cmake
cpucount=`nproc`

make -j${cpucount}