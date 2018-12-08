cmake_minimum_required(VERSION 3.10.2 FATAL_ERROR)

project("BeagleBoneIO" LANGUAGES C CXX)

add_library(${PROJECT_NAME}
  STATIC
  src/LEDControl.cpp
  src/OnBoardButtons.cpp
  src/EncoderEqep.cpp
  src/MotorChannel.cpp
  )

target_compile_features(${PROJECT_NAME}
  PUBLIC cxx_std_17
  )

set_target_properties(${PROJECT_NAME}
  PROPERTIES
  CXX_STANARD 17
  CXX_EXTENSIONS OFF
  CXX_STANARD_REQUIRED ON
  POSITION_INDEPENDENT_CODE ON
  )

target_include_directories(${PROJECT_NAME}
  PUBLIC
  ./include
  )

target_link_libraries(${PROJECT_NAME}
  PRIVATE
  robotics_cape
  CompilerSetup
  )
