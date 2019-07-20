# Project wide setup that can be included by library users

set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# Always use '-fPIC'/'-fPIE' option.
set( CMAKE_POSITION_INDEPENDENT_CODE ON )

option(TARGET_BEAGLEBONE OFF "Build for beaglebone target")
message(STATUS "Targeting beaglebone: ${TARGET_BEAGLEBONE}")

if(TARGET_BEAGLEBONE)
  # Static linking is disabled when not building for target
  # This is in order for sanatizers to work
  link_libraries("-static") # avoid /lib/arm-linux-gnueabihf/libc.so.6: version `GLIBC_2.27' not found on target
endif()

find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
  message("Using ccache if using Ninja or unix make.")
  set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
endif()
