function(cppcheckSetup sourcesToCheck)

if(NOT CPPCHECK_EXECUTABLE)
  set(CPPCHECK_EXECUTABLE cppcheck)
endif()

if(NOT EXISTS ${CPPCHECK_EXECUTABLE})
  find_program(clangformat_executable_tmp ${CPPCHECK_EXECUTABLE})
  if(clangformat_executable_tmp)
    set(CLANGFORMAT_EXECUTABLE ${CPPCHECK_EXECUTABLE})
    unset(clangformat_executable_tmp)
  else()
    message(FATAL_ERROR "CppCheckTarget: ${CPPCHECK_EXECUTABLE} not found! Aborting")
  endif()
endif()

foreach(src ${sourcesToCheck})
  get_filename_component(src ${src} ABSOLUTE)
  list(APPEND srcs ${src})
endforeach()
#set(srcs "${srcs_tmp}")
unset(srcs_tmp)

include(ProcessorCount)
ProcessorCount(N)

message(STATUS "Cppcheck on: ${srcs}")

add_custom_target(${PROJECT_NAME}_cppcheck
  COMMAND cppcheck
  ${srcs}
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
  --suppress=unusedFunction
  COMMENT "Cppcheck with ${CPPCHECK_EXECUTABLE} ..."
  )

if(TARGET cppcheck)
  add_dependencies(cppcheck ${PROJECT_NAME}_cppcheck)
else()
  add_custom_target(cppcheck DEPENDS ${PROJECT_NAME}_cppcheck)
endif()

endfunction()
