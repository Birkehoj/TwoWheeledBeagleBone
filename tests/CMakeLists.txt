cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

project("TestTwoWheeledBeagleBone" LANGUAGES CXX)

option(ENABLE_UNIT_TESTS ON "Enable unit tests")
message(STATUS "Enable testing: ${ENABLE_UNIT_TESTS}")

if(ENABLE_UNIT_TESTS)

  add_executable(${PROJECT_NAME})
  target_sources(${PROJECT_NAME}
    PRIVATE
      test.cpp
      testLEDControl.cpp
    )

  set(_catch2_version 2.6.1)
  find_package(Catch2 ${_catch2_version} REQUIRED)

  if(TARGET Catch2::Catch2)
    message(STATUS "Using Catch2 version ${_catch2_version} from system library")
  else()
    message(WARNING "Failed to find Catch2 version ${_catch2_version} on system.")
    message(STATUS "Please install Catch2 for shorter configuration time")
    message(STATUS "Catch2 will be downloaded on configuration time and used until you install it")
    include(FetchContent)
    FetchContent_Declare(
      Catch2
      GIT_REPOSITORY "https://github.com/catchorg/Catch2"
      GIT_TAG        v${_catch2_version}
      )

    FetchContent_GetProperties(Catch2)
    if(NOT Catch2_POPULATED)
      FetchContent_Populate(Catch2)
      add_subdirectory(
        ${catch2_SOURCE_DIR} ${catch2_BINARY_DIR}
        EXCLUDE_FROM_ALL
        )
    endif()
    list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/contrib)
  endif()

  target_link_libraries(${PROJECT_NAME}
    PRIVATE
      CompilerSetup
      BeagleBoneIO
      Catch2::Catch2
    )

  include(CTest)
  set(BUILD_TESTING OFF)

  find_package(MPI)
  if(MPI_FOUND)
    set(OptionalCatchTestLauncher ${MPIEXEC_EXECUTABLE} ${MPIEXEC_NUMPROC_FLAG} ${MPIEXEC_MAX_NUMPROCS})
  else()
      message(INFO "Failed to find MPI on system install mpiexec to run tests in parallel")
  endif()

  include(Catch)
  catch_discover_tests(${PROJECT_NAME})

  include(ParseAndAddCatchTests)
  ParseAndAddCatchTests(${PROJECT_NAME})

  add_custom_target(
    run_tests
    COMMAND $<TARGET_FILE:TestTwoWheeledBeagleBone>
    )
endif()
