cmake_minimum_required(VERSION 3.13.4 FATAL_ERROR)

# additional target to perform cpplint run, requires cpplint
add_custom_target(
  cpplint
  COMMAND cpplint
  --recursive
  --extensions=hpp,cpp,h,c
  ${CMAKE_SOURCE_DIR}/BeagleBoneIO/
  ${CMAKE_SOURCE_DIR}/TwoWheeledRobot/
  )
