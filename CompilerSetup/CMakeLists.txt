cmake_minimum_required(VERSION 3.10.2 FATAL_ERROR)

project("CompilerSetup")

add_library(${PROJECT_NAME} INTERFACE)

set(_common_compiler_warnings_flag
  # Standard GCC stuff
  -Wall
  -Wextra # reasonable and standard
  -Wshadow # warn the user if a variable declaration shadows one from a
  # parent context
  -Wnon-virtual-dtor # warn the user if a class with virtual functions has a
  # non-virtual destructor. This helps catch hard to
  # track down memory errors
  -Wold-style-cast # warn for c-style casts
  -Wcast-align # warn for potential performance problem casts
  -Wunused # warn on anything being unused
  -Woverloaded-virtual # warn if you overload (not override) a virtual
  # function
  -Wpedantic # warn if non-standard C++ is used
  -Wconversion # warn on type conversions that may lose data
  -Wsign-conversion # warn on sign conversions
  # do not exist
  # probably wanted
  -Wnull-dereference # warn if a null dereference is detected
  -Wdouble-promotion # warn if float is implicit promoted to double
  -Wformat=2 # warn on security issues around functions that format output
  -Wpadded
  -Wnull-dereference
  -Wold-style-cast
  -Wshadow
  -Wformat=2
  -Weffc++
  -Werror=implicit-function-declaration
  -Wno-unknown-pragmas # allows for inline compiler specific ignore warnings
  )

set(_gcc_compiler_warnings_flags
  -Wduplicated-cond # warn if if / else chain has duplicated conditions
  -Wduplicated-branches # warn if if / else branches have duplicated code
  -Wlogical-op # warn about logical operations being used where bitwise were

  -Wmisleading-indentation # warn if identation implies blocks where blocks
  -Wsuggest-final-types
  -Wsuggest-final-methods
  -Wsuggest-override
  # probably wanted
  -Wlogical-op
  -Wuseless-cast # warn if you perform a cast to the same type
  -Wduplicated-cond
  -Wduplicated-branches
  -Wuseless-cast

  # Might not be wanted in the future
  #						-Wno-c++98-compat
  #						-Wno-c++98-compat-pedantic
  #						-Wno-exit-time-destructors
  #						-Wno-global-constructors
  #						-Wno-gnu-zero-variadic-macro-arguments
  #						-Wno-documentation
  #						-Wno-switch-enum
  #						-Wno-missing-prototypes
  #						-Wno-used-but-marked-unused
  )

set(_clang_compiler_warnings
  -Weverything
  -Wno-c++98-compat
  -Wno-c++98-compat-pedantic
  )

set(_cxx_flags_debug
  -O1
  )

set(_cxx_flags_release
  -O3
  )

set(_beaglebone_build_optimizations
  -mcpu=cortex-a8
  -mhard-float
  -mfloat-abi=hard
  -mfpu=neon
  -mtune=cortex-a8
  )

target_compile_options(${PROJECT_NAME}
  INTERFACE

  # clang/GCC warnings
  $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>:
  ${_common_compiler_warnings_flag}>

  # GCC warnings
  $<$<CXX_COMPILER_ID:GNU>:${_gcc_compiler_warnings_flags}>

  # clang warnings
  $<$<CXX_COMPILER_ID:Clang>:${_clang_compiler_warnings}>

  $<$<CONFIG:Debug>:${_cxx_flags_debug}>
  $<$<CONFIG:Release>:${_cxx_flags_release}>

  # Platform specific optimizations
  $<$<BOOL:TARGET_BEAGLEBONE>:${_beaglebone_build_optimizations}>
  )
