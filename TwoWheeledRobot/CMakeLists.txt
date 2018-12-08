cmake_minimum_required(VERSION 3.10.2 FATAL_ERROR)

project("TwoWheeledRobot" LANGUAGES C CXX)

add_executable(${PROJECT_NAME}
  src/main.cpp
  )

# Link time optimizations for release builds
#set_property(TARGET ${PROJECT_NAME} PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)

set_target_properties(${PROJECT_NAME}
  PROPERTIES
  CXX_STANARD 17
  CXX_EXTENSIONS OFF
  CXX_STANARD_REQUIRED ON
  POSITION_INDEPENDENT_CODE 1
  )

target_compile_features(${PROJECT_NAME}
  PUBLIC cxx_std_17
  )

target_link_libraries(${PROJECT_NAME}
  PRIVATE
  BeagleBoneIO
  CompilerSetup
  )

target_include_directories(${PROJECT_NAME}
  PUBLIC
  include
  )
