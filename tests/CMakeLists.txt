cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

project("TestTwoWheeledBeagleBone" LANGUAGES CXX)

if(ENABLE_UNIT_TESTS)
  include(FetchContent)

  FetchContent_Declare(
    Catch2
    GIT_REPOSITORY "https://github.com/catchorg/Catch2"
    GIT_TAG        v2.6.1
    )

  FetchContent_GetProperties(Catch2)
  if(NOT Catch2_POPULATED)
    FetchContent_Populate(Catch2)
    add_subdirectory(
      ${catch2_SOURCE_DIR} ${catch2_BINARY_DIR}
      EXCLUDE_FROM_ALL
      )
  endif()

  add_executable(${PROJECT_NAME} "")

  target_sources(${PROJECT_NAME}
    PRIVATE
      test.cpp
      testLEDControl.cpp
    )

  target_link_libraries(${PROJECT_NAME}
    PRIVATE
      CompilerSetup
      BeagleBoneIO
      Catch2
    )

  include(CTest)
  set(BUILD_TESTING OFF)

  find_package(MPI)
  if(MPI_FOUND)
    set(OptionalCatchTestLauncher ${MPIEXEC_EXECUTABLE} ${MPIEXEC_NUMPROC_FLAG} ${MPIEXEC_MAX_NUMPROCS})
  else()
      message(INFO "Failed to find MPI on system install mpiexec to run tests in parallel")
  endif()

  # Discover tests
  list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/contrib)

  include(Catch)
  catch_discover_tests(${PROJECT_NAME})

  include(ParseAndAddCatchTests)
  ParseAndAddCatchTests(${PROJECT_NAME})

  add_custom_target(
    run_tests
    COMMAND $<TARGET_FILE:TestTwoWheeledBeagleBone>
    )
endif()
