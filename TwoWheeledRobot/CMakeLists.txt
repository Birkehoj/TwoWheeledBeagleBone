cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project("TwoWheeledRobot" LANGUAGES C CXX)

SET(C_COMPILER /usr/bin/arm-linux-gnueabi-gcc-8)
SET(CXX_COMPILER /usr/bin/arm-linux-gnueabi-gcc-8)

set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

list(APPEND _sources
	src/main.cpp
)

add_executable("TwoWheeledRobot" ${_sources})

set_target_properties("TwoWheeledRobot"
	PROPERTIES
	CXX_STANARD 17
	CXX_EXTENSIONS OFF
	CXX_STANARD_REQUIRED ON
	POSITION_INDEPENDENT_CODE 1
)

target_compile_features("TwoWheeledRobot"
	PUBLIC cxx_std_17
)

target_link_libraries("TwoWheeledRobot"
	PRIVATE
		BeagleBoneIO
)

target_include_directories("TwoWheeledRobot"
	PUBLIC
		include
)
