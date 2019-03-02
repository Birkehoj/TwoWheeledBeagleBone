cmake_minimum_required(VERSION 3.13)

# Preable
project("BeagleBoneIO" LANGUAGES C CXX)
set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/" )

# Project wide setup
option(TARGET_BEAGLEBONE OFF "Build for beaglebone target")
message(STATUS "Targeting beaglebone: ${TARGET_BEAGLEBONE}")

set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

# Always use '-fPIC'/'-fPIE' option.
set( CMAKE_POSITION_INDEPENDENT_CODE ON )

link_libraries("-static")

# Dependencies
add_subdirectory("ExternalDependencies")

# Static analysis
include(ProcessorCount)
ProcessorCount(N)

set(CMAKE_CXX_CPPLINT cpplint
  --quiet
  --recursive
  --extensions=hpp,cpp,h,c
  ${CMAKE_CURRENT_LIST_DIR}/src
  ${CMAKE_CURRENT_LIST_DIR}/include
  )

set(CMAKE_CXX_CPPCHECK cppcheck
  ${CMAKE_CURRENT_LIST_DIR}/src ${CMAKE_CURRENT_LIST_DIR}/include
  --enable=all
  --std=c++14
#  --verbose
  --quiet
  --inconclusive
  --force
  --inline-suppr
  --language=c++
  --verbose
  --error-exitcode=1
  --suppress=unusedFunction
  -j${N}
  -I${CMAKE_CURRENT_LIST_DIR}/include
  -i${CMAKE_CURRENT_LIST_DIR}/ExternalDependencies/LibRobotControl/*
  -I${CMAKE_CURRENT_LIST_DIR}/ExternalDependencies/LibRobotControl/LibRobotControl/library/include
  )

if(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
  message(STATUS "Clang compiler detected, enabling clang tidy checks on builds.")

  set(CMAKE_CXX_CLANG_TIDY clang-tidy
    -p ${CMAKE_BINARY_DIR}
    -header-filter='.*'
    )
  set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
endif()


# Main build targets
add_library(${PROJECT_NAME})
add_subdirectory("CompilerSetup")
add_subdirectory(src)

# Tests
add_subdirectory("tests")

# Packagaging
target_sources(${PROJECT_NAME}
  PRIVATE
    # Headers
    include/BeagleBoneIO/EncoderEqep.h
    include/BeagleBoneIO/LEDControl.h
    include/BeagleBoneIO/MotorsController.h
    include/BeagleBoneIO/OnBoardButtons.h
  # Sources
    src/EncoderEqep.cpp
    src/LEDControl.cpp
    src/MotorsController.cpp
    src/OnBoardButtons.cpp
  )

target_compile_features(${PROJECT_NAME}
  PUBLIC
    cxx_std_17
  )

include(CheckIPOSupported)
check_ipo_supported(RESULT ipoSupported)

# TODO: Figure out why IWYU gives many warnings that seems like false positives at first sight
#find_program(iwyu_path NAMES include-what-you-use iwyu)
#set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_INCLUDE_WHAT_YOU_USE "${iwyu_path};-Xiwyu;any;-Xiwyu;iwyu;-Xiwyu;args;-Xiwyu;--transitive_includes_only;-Xiwyu;--verbose=3 -Wno-unknown-warning-option")
#  ;-Xiwyu;--transitive_includes_only --cwd=${CMAKE_CURRENT_SOURCE_DIR};-Xiwyu;--verbose=3")

set_target_properties(${PROJECT_NAME}
  PROPERTIES
    CXX_EXTENSIONS OFF
    CXX_STANARD 17
    CXX_STANARD_REQUIRED ON
    INTERPROCEDURAL_OPTIMIZATION ${ipoSupported}
    LINK_WHAT_YOU_USE TRUE
    POSITION_INDEPENDENT_CODE ON
  )

target_include_directories(${PROJECT_NAME}
  PUBLIC
    ./include
  )

target_link_libraries(${PROJECT_NAME}
  PRIVATE
    CompilerSetup
    robotics_cape
  )
