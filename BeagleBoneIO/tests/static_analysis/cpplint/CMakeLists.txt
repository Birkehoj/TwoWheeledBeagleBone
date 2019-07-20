cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

# additional target to perform cpplint run, requires cpplint
add_custom_target(
  cpplint
  COMMAND cpplint
  --recursive
  --extensions=hpp,cpp,h,c
  ${CMAKE_SOURCE_DIR}/BeagleBoneIO/src
  ${CMAKE_SOURCE_DIR}/BeagleBoneIO/include
  ${CMAKE_SOURCE_DIR}/TwoWheeledRobot/src
  ${CMAKE_SOURCE_DIR}/TwoWheeledRobot/include
  )
