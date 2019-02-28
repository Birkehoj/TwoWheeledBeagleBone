cmake_minimum_required(VERSION 3.13.4 FATAL_ERROR)

# additional target to perform cppcheck run, requires cppcheck
include(ProcessorCount)
ProcessorCount(N)

add_custom_target(
  run-clang-tidy
  COMMAND run-clang-tidy
  -j ${N}
  -p ${CMAKE_BINARY_DIR}
  -header-filter='.*'
  -quiet
)

