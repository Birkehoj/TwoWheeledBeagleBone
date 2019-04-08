cmake_minimum_required(VERSION 3.13)

find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
  message("Using ccache if using Ninja or unix make.")
  set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
endif()

# Preable
project(BeagleBoneIO LANGUAGES C CXX)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake/)

# Project wide setup
option(TARGET_BEAGLEBONE OFF "Build for beaglebone target")
message(STATUS "Targeting beaglebone: ${TARGET_BEAGLEBONE}")

set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

# Always use '-fPIC'/'-fPIE' option.
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

link_libraries("-static")

set(LIBRARY_TARGET_NAME BeagleBoneIO_beagleBoneIO)

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

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(cppcheckPlatform unix64)
  else()
    set(cppcheckPlatform unix32)
  endif()
endif()

set(CMAKE_CXX_CPPCHECK cppcheck
  ${CMAKE_CURRENT_LIST_DIR}/src
  ${CMAKE_CURRENT_LIST_DIR}/include
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
#  --check-library
  --platform=${cppcheckPlatform}
  -j${N}
  -I${CMAKE_CURRENT_LIST_DIR}/include
  -i${CMAKE_CURRENT_LIST_DIR}/ExternalDependencies/LibRobotControl/*
  -I${CMAKE_CURRENT_LIST_DIR}/ExternalDependencies/LibRobotControl/LibRobotControl/library/include
  )
unset(cppcheckPlatform)

if(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
  message(STATUS "Clang compiler detected, enabling clang tidy checks on builds.")

  set(CMAKE_CXX_CLANG_TIDY clang-tidy-7
    -p ${CMAKE_BINARY_DIR}
    -header-filter='.*'
    )
  set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

  find_program(iwyu_path NAMES include-what-you-use iwyu)
  set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE "${iwyu_path};-Xiwyu;any;-Xiwyu;iwyu;-Xiwyu;args;-Xiwyu;--transitive_includes_only;-Xiwyu;--verbose=3 -Wno-unknown-warning-option")
endif()

# Main build targets
add_library(${LIBRARY_TARGET_NAME})
add_library(BeagleBoneIO::BeagleBoneIO_beagleBoneIO ALIAS ${LIBRARY_TARGET_NAME})

add_subdirectory(CompilerSetup)
add_subdirectory(src)

target_sources(${LIBRARY_TARGET_NAME}
  PRIVATE
    # Headers
    include/BeagleBoneIO/EncoderEqep.h
    include/BeagleBoneIO/LEDControl.h
    include/BeagleBoneIO/MotorsController.h
    include/BeagleBoneIO/OnBoardButtons.h
  )

target_compile_features(${LIBRARY_TARGET_NAME}
  PUBLIC
    cxx_std_17
  )

include(CheckIPOSupported)
check_ipo_supported(RESULT ipoSupported)

set_target_properties(${LIBRARY_TARGET_NAME}
  PROPERTIES
    CXX_EXTENSIONS OFF
    CXX_STANARD 17
    CXX_STANARD_REQUIRED ON
    INTERPROCEDURAL_OPTIMIZATION ${ipoSupported}
    LINK_WHAT_YOU_USE TRUE
    POSITION_INDEPENDENT_CODE ON
  )

target_include_directories(${LIBRARY_TARGET_NAME}
  PUBLIC
    ./include
  )

target_link_libraries(${LIBRARY_TARGET_NAME}
  PRIVATE
    CompilerSetup
    robotics_cape
  )

# Tests
add_subdirectory("tests")

# Packagaging


# Various Testing and formating targets
#include(SourcesFromTarget)
#getSourcePaths(${LIBRARY_TARGET_NAME} absSourcePaths)
include(CppCheckTarget)
cppcheckSetup(${LIBRARY_TARGET_NAME})
#unset(absSourcePaths)

option(CLANGFORMAT "Setup clangformat target" ON)
if(CLANGFORMAT)
  include(ClangFormat)

  get_target_property(BeagleBoneIO_sources ${LIBRARY_TARGET_NAME} SOURCES)

  # Setup clangformat target
  clangformat_setup("${BeagleBoneIO_sources}")
  unset(BeagleBoneIO_sources)
endif()
