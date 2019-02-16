cmake_minimum_required(VERSION 3.10.2 FATAL_ERROR)

project("TwoWheeledBeagleBone" LANGUAGES C CXX)

include(cppcheck.cmake)
include(cpplint.cmake)
include(IncludeWhatYouUse.cmake)

set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
#set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

link_libraries("-static")

add_subdirectory("LibRobotControl/library")
add_subdirectory("BeagleBoneIO")
add_subdirectory("TwoWheeledRobot")
add_subdirectory("CompilerSetup")
