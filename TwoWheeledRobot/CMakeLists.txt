cmake_minimum_required(VERSION 3.10.2 FATAL_ERROR)

project("TwoWheeledRobot" LANGUAGES C CXX)

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

target_compile_options("TwoWheeledRobot"
  PUBLIC
  ${CXX_FLAGS}
  )

target_link_libraries("TwoWheeledRobot"
  PRIVATE
  BeagleBoneIO
  )

target_include_directories("TwoWheeledRobot"
  PUBLIC
  include
  )
