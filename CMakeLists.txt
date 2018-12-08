cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project("TwoWheeledBeagleBone" LANGUAGES C CXX)

include(cppcheck.cmake)
include(cpplint.cmake)

set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
#set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

link_libraries("-static") # This seems like a hack

add_subdirectory("LibRobotControl/library")
add_subdirectory("BeagleBoneIO")
add_subdirectory("TwoWheeledRobot")
add_subdirectory("CompilerSetup")
