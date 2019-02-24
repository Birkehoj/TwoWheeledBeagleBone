#!/bin/bash

arm_id="gcc-arm"
clang_id="clang"
gcc_id="gcc"

build_prepend_path="build-"

arm_build_path=$build_prepend_path$arm_id
clag_build_path=$build_prepend_path$clang_id
gcc_build_path=$build_prepend_path$gcc_id

cpucount=`nproc`

build_in_folder () {
	build_target=$1
	build_path="$build_prepend_path$build_target"

	if [[ ! -d $build_path ]]; then
		mkdir -p $build_path
	fi

	cd $build_path

	cmake_arguments=$2
	cmake .. $cmake_arguments -DCMAKE_BUILD_TYPE=$build_configuration -DCMAKE_CXX_FLAGS=-Werror

	if [[ $? -ne 0 ]]; then
		echo "Failed to configure build for target; $build_target. Exiting"
		cd ..
		exit 1
	fi

	cmake --build . --clean-first -- -j${cpucount} # --clean-first 

	if [[ $? -ne 0 ]]; then
		echo "Failed to compile for target; $build_target. Exiting"
		cd ..
		exit 1
	else
		report_past_test "build for target $build_target"	
	fi
	cd ..
}

report_past_test()
{
	echo -e "\e[32m$1 \e[39m: \033[1;32m\xE2\x9C\x93 passed \033[0m";
}

run_clang_tidy_checks()
{
	clang_folder_name="build-$clang_id"
	cmake --build $clang_folder_name --target run-clang-tidy -- -j${cpucount} > clang-tidy-warnings.txt

	echo $clang-tidy-warnings

	if [[ -n $(grep "warning: " clang-tidy-warnings.txt) ]] || [[ -n $(grep "error: " clang-tidy-warnings.txt) ]]; then
	    echo "Clang-tidy checks failed"
	    echo ""
	    grep --color -E '^|warning: |error: ' clang-tidy-warnings.txt
	    echo "Please correct clang-tidy warnings"
	    rm clang-tidy-warnings.txt
	    exit -1;
	else
	    report_past_test clang-tidy
	    rm clang-tidy-warnings.txt
	fi
}

run_cppcheck()
{
	cmake --build $1 --target cppcheck -- -j${cpucount}
	if [[ $? -ne 0 ]]; then
		echo "Cppcheck failed Exiting"
		exit 1
	else
		report_past_test "cppcheck"
	fi
}

run_cpplint()
{
	cmake --build $1 --target cpplint -- -j${cpucount}
	if [[ $? -ne 0 ]]; then
		echo "Cpplint failed Exiting"
		exit 1
	else
		report_past_test "cpplint"
	fi
}

# Main

if [[ "$1" == "Debug" || "$1" == "Release" ]]; then
	build_configuration=$1
else
	echo "Please supply a valid build configuration; [Debug, Release]"
	exit 1
fi


build_in_folder $arm_id "-DCMAKE_TOOLCHAIN_FILE=arm-toolchain.cmake"
build_in_folder  $clang_id "-DCMAKE_CXX_COMPILER=clang++ -DCMAKE_C_COMPILER=clang"
build_in_folder $gcc_id "-DCMAKE_CXX_COMPILER=g++-8 -DCMAKE_C_COMPILER=gcc-8"

run_clang_tidy_checks

run_cppcheck $arm_build_path

run_cpplint $arm_build_path

echo "Fixing formatting in BeagleboneIO"
find BeagleBoneIO -regex '.*\.\(cpp\|h\|hpp\|cc\)' -exec clang-format -style=file -i {} \;

exit 0