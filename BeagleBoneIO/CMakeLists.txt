cmake_minimum_required(VERSION 3.10.2 FATAL_ERROR)

project("BeagleBoneIO" LANGUAGES C CXX)

add_library(${PROJECT_NAME} STATIC)

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

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

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
