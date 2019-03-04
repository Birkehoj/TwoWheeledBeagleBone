function(cppcheckSetup target)

if(NOT CPPCHECK_EXECUTABLE)
  set(CPPCHECK_EXECUTABLE cppcheck)
endif()

if(NOT EXISTS ${CPPCHECK_EXECUTABLE})
  find_program(cppcheck_executable_tmp ${CPPCHECK_EXECUTABLE})
  if(cppcheck_executable_tmp)
    set(CLANGFORMAT_EXECUTABLE ${CPPCHECK_EXECUTABLE})
    unset(cppcheck_executable_tmp)
  else()
    message(FATAL_ERROR "CppCheckTarget: ${CPPCHECK_EXECUTABLE} not found! Aborting")
  endif()
endif()


get_target_property(target_sources ${target} SOURCES)

foreach(target_src ${target_sources})
  get_filename_component(target_src ${target_src} ABSOLUTE)
  list(APPEND srcs ${target_src})
endforeach()

unset(srcs_tmp)

get_target_property(target_includes ${target} INCLUDE_DIRECTORIES)

foreach(target_include ${target_includes})
  get_filename_component(target_include ${target_include} ABSOLUTE)
  list(APPEND includes ${target_include})
endforeach()

include(ProcessorCount)
ProcessorCount(N)

add_custom_target(${PROJECT_NAME}_cppcheck
  COMMAND cppcheck
  ${srcs}
  ${includes}
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
