cmake_minimum_required(VERSION 3.10.2 FATAL_ERROR)

project("BeagleBoneIO" LANGUAGES C CXX)

add_library(${PROJECT_NAME}
  STATIC
  src/LEDControl.cpp
  src/OnBoardButtons.cpp
  src/EncoderEqep.cpp
  src/MotorsController.cpp
  )

target_compile_features(${PROJECT_NAME}
  PUBLIC cxx_std_17
  )

include(CheckIPOSupported)
check_ipo_supported(RESULT ipoSupported)

# TODO: Figure out why IWYU gives many warnings that seems like false positives at first sight
#find_program(iwyu_path NAMES include-what-you-use iwyu)
#set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_INCLUDE_WHAT_YOU_USE "${iwyu_path};-Xiwyu;any;-Xiwyu;iwyu;-Xiwyu;args;-Xiwyu;--transitive_includes_only;-Xiwyu;--verbose=3 -Wno-unknown-warning-option")
#  ;-Xiwyu;--transitive_includes_only --cwd=${CMAKE_CURRENT_SOURCE_DIR};-Xiwyu;--verbose=3")

set_target_properties(${PROJECT_NAME}
  PROPERTIES
  CXX_STANARD 17
  CXX_EXTENSIONS OFF
  CXX_STANARD_REQUIRED ON
  POSITION_INDEPENDENT_CODE ON
  INTERPROCEDURAL_OPTIMIZATION ${ipoSupported}
  LINK_WHAT_YOU_USE TRUE
  )

target_include_directories(${PROJECT_NAME}
  PUBLIC
  ./include
  )

target_link_libraries(${PROJECT_NAME}
  PRIVATE
  robotics_cape
  CompilerSetup
  )
