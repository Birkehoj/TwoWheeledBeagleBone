cmake_minimum_required(VERSION 3.13.4 FATAL_ERROR)

# additional target to perform cppcheck run, requires cppcheck
include(ProcessorCount)
ProcessorCount(N)
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(cppcheckPlatform unix64)
  else()
    set(cppcheckPlatform unix32)
  endif()
endif()

# This relative path is sad
set(src_root_dir ${CMAKE_CURRENT_LIST_DIR}/../../../)

add_custom_target(
  cppcheck_target
  COMMAND cppcheck
  ${src_root_dir}/src
  ${src_root_dir}/include
  --enable=all
  --std=c++14
  --verbose
  --quiet
  --enable=warning
  --inconclusive
  --force
  --inline-suppr
  --language=c++
  --verbose
  --error-exitcode=1
  -j${N}
    --platform=${cppcheckPlatform}
  --suppress=unusedFunction
  -I${src_root_dir}/include
  -i${src_root_dir}/ExternalDependencies/LibRobotControl/*
  -I${src_root_dir}/ExternalDependencies/LibRobotControl/LibRobotControl/library/include
#  --xml
#  --check-config
#  --check-library
#  --template='{file}:{line},{severity},{id},{message}'
#  --suppress=syntaxError # c++17 features not supported # Unmatched suppression
#  --suppress=missingIncludeSystem # Unmatched suppression
)
