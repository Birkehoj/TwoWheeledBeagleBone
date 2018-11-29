cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project("TwoWheeledBeagleBone" LANGUAGES C CXX)

set(CMAKE_CXX_CPPCHECK cppcheck)
find_program(CMAKE_CXX_CPPCHECK NAMES cppcheck)
if (CMAKE_CXX_CPPCHECK)
	list(
		APPEND CMAKE_CXX_CPPCHECK
			"--enable=all"
#			"--enable=warning"
#			"--inconclusive"
#			"--force"
			"--inline-suppr"
			"--language=c++"
#			"-v"
			"--library=std"
			"--suppressions-list=${CMAKE_SOURCE_DIR}/CppCheckSuppressions.txt"
	)
endif()
set(CMAKE_CXX_CPPLINT cpplint)

set(CMAKE_CXX_CLANG_TIDY clang-tidy checks=-*,readability-*)

set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

link_libraries("-static") # This seems like a hack

add_subdirectory("LibRobotControl/library")
add_subdirectory("BeagleBoneIO")
add_subdirectory("WheelController")
add_subdirectory("TwoWheeledRobot")
