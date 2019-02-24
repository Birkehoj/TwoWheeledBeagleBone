cmake_minimum_required(VERSION 3.10.2 FATAL_ERROR)

project("TwoWheeledBeagleBone" LANGUAGES C CXX)

include(cppcheck.cmake)
include(cpplint.cmake)
include(clang-tidy.cmake)
message("Binary dir ${CMAKE_BINARY_DIR}")

set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
#set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Always use '-fPIC'/'-fPIE' option.
set( CMAKE_POSITION_INDEPENDENT_CODE ON )

link_libraries("-static")

#add_subdirectory("LibRobotControl/library")
add_subdirectory("ExternalDependencies")
add_subdirectory("BeagleBoneIO")
add_subdirectory("TwoWheeledRobot")
add_subdirectory("CompilerSetup")
