cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

project("TwoWheeledBeagleBone" LANGUAGES C CXX  VERSION 0.0.1)

# Preable
find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
  message("Using ccache if using Ninja or unix make.")
  set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
endif()

set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/" )

# Dependencies
add_subdirectory("dependencies")

# Main build targets
add_subdirectory("BeagleBoneIO")
add_subdirectory("TwoWheeledRobot")

# Tests
add_subdirectory("tests")

# Packagaging
