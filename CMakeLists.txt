cmake_minimum_required(VERSION 3.13.4 FATAL_ERROR)

# Preable
project("TwoWheeledBeagleBone" LANGUAGES C CXX  VERSION 0.0.1)
set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/" )

set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
#set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Always use '-fPIC'/'-fPIE' option.
set( CMAKE_POSITION_INDEPENDENT_CODE ON )

link_libraries("-static")

# Dependencies
add_subdirectory("dependencies")

# Main build targets
add_subdirectory("BeagleBoneIO")
add_subdirectory("TwoWheeledRobot")

# Tests
add_subdirectory("tests")

# Packagaging
