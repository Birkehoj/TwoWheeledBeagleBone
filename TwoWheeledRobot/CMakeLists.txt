cmake_minimum_required(VERSION 3.10.2 FATAL_ERROR)

project("TwoWheeledRobot" LANGUAGES C CXX)

add_executable(${PROJECT_NAME}
  src/main.cpp
  )

include(CheckIPOSupported)
check_ipo_supported(RESULT ipoSupported)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set_target_properties(${PROJECT_NAME}
  PROPERTIES
    CXX_EXTENSIONS OFF
    CXX_STANARD 17
    CXX_STANARD_REQUIRED ON
    INTERPROCEDURAL_OPTIMIZATION ${ipoSupported}
    LINK_WHAT_YOU_USE TRUE
    POSITION_INDEPENDENT_CODE 1
  )

target_compile_features(${PROJECT_NAME}
  PUBLIC
    cxx_std_17
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
