cmake_minimum_required(VERSION 3.13.4 FATAL_ERROR)

find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
  message("Using ccache if using Ninja or unix make.")
  set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
endif()

project(TwoWheeledRobot LANGUAGES C CXX)

add_executable(TwoWheeledRobot_TwoWheeledRobot
  src/main.cpp
  )
set_target_properties(TwoWheeledRobot_TwoWheeledRobot PROPERTIES OUTPUT_NAME TwoWheeledRobot)

include(CheckIPOSupported)
check_ipo_supported(RESULT ipoSupported)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set_target_properties(TwoWheeledRobot_TwoWheeledRobot
  PROPERTIES
    CXX_EXTENSIONS OFF
    CXX_STANARD 17
    CXX_STANARD_REQUIRED ON
    INTERPROCEDURAL_OPTIMIZATION ${ipoSupported}
    LINK_WHAT_YOU_USE TRUE
    POSITION_INDEPENDENT_CODE 1
  )

target_compile_features(TwoWheeledRobot_TwoWheeledRobot
  PUBLIC
    cxx_std_17
  )

target_link_libraries(TwoWheeledRobot_TwoWheeledRobot
  PRIVATE
    BeagleBoneIO::BeagleBoneIO_beagleBoneIO
    CompilerSetup
  )

target_include_directories(TwoWheeledRobot_TwoWheeledRobot
  PUBLIC
    include
  )
