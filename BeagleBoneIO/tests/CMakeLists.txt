cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

project("TestTwoWheeledBeagleBone" LANGUAGES CXX)

#option(ENABLE_UNIT_TESTS "Enable unit tests." ON)
#message(STATUS "Enable testing: ${ENABLE_UNIT_TESTS}")

if(BUILD_TESTING)

  set(_catch2_version 2.9.1)
  find_package(Catch2 ${_catch2_version} REQUIRED)

  if(TARGET Catch2::Catch2)
    message(STATUS "Using Catch2 version ${_catch2_version} from system library.")
  else()
    message(WARNING "Failed to find Catch2 version ${_catch2_version} on system.")
    message(STATUS "Please install Catch2 for shorter configuration time.")
    message(STATUS "Catch2 will be downloaded on configuration time and used until you install it.")
    include(FetchContent)
    FetchContent_Declare(
      Catch2
      GIT_REPOSITORY "https://github.com/catchorg/Catch2"
      GIT_TAG        v${_catch2_version}
      )

    FetchContent_GetProperties(Catch2)
    if(NOT Catch2_POPULATED)
      FetchContent_Populate(Catch2)
      set(BUILD_TESTING OFF)
      add_subdirectory(
        ${catch2_SOURCE_DIR} ${catch2_BINARY_DIR}
        EXCLUDE_FROM_ALL
        )
    endif()
    list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/contrib)
  endif()

  add_executable(${PROJECT_NAME})
  target_sources(${PROJECT_NAME}
    PRIVATE
      test.cpp
      testLEDControl.cpp
    )

  target_link_libraries(${PROJECT_NAME}
    PRIVATE
      CompilerSetup
      BeagleBoneIO::BeagleBoneIO_beagleBoneIO
      Catch2::Catch2
    )

  include(CTest)

  find_package(MPI)
  if(MPI_FOUND)
    set(OptionalCatchTestLauncher ${MPIEXEC_EXECUTABLE} ${MPIEXEC_NUMPROC_FLAG} ${MPIEXEC_MAX_NUMPROCS})
  else()
      message(STATUS "Failed to find MPI on system. Install mpiexec to run tests in parallel.")
  endif()

  include(Catch)
  catch_discover_tests(${PROJECT_NAME})

  include(ParseAndAddCatchTests)
  ParseAndAddCatchTests(${PROJECT_NAME})

  add_custom_target(
    run_tests
    COMMAND $<TARGET_FILE:${PROJECT_NAME}>
    )

  # Address sanatizers
  if(ECM_ENABLE_SANITIZERS)
    find_package(ECM REQUIRED NO_MODULE)
    list(APPEND CMAKE_MODULE_PATH ${ECM_MODULE_DIR})
    include(ECMEnableSanitizers)
  endif()
endif()

add_subdirectory(static_analysis)
