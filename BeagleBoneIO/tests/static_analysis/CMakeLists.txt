cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

option(ENABLE_STATIC_ANALYSIS "Enable static analysis." ON)
message(STATUS "Enable static analysis: ${ENABLE_STATIC_ANALYSIS}")

if(ENABLE_STATIC_ANALYSIS)
  add_subdirectory(cppcheck)
  add_subdirectory(cpplint)
  add_subdirectory(clangtidy)
endif()
