cmake_minimum_required(VERSION 3.13.4 FATAL_ERROR)

project("CompilerSetup")

add_library(${PROJECT_NAME} INTERFACE)

set(_clang_gcc_compiler_warnings_flag
  # Standard stuff
  -Wall
  -Wextra # reasonable and standard
  -Wpedantic
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
#  -Werror=implicit-function-declaration
  -Wno-unknown-pragmas # allows for inline compiler specific ignore warnings
  -Wno-c++98-compat
  -Wno-c++98-compat-pedantic
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

  # Linker
  -Wl,-z,defs # Detect and reject underlinking
  -Wl,-z,now #Disable lazy binding

  # Might not be wanted in the future

  # -Wno-exit-time-destructors
  # -Wno-global-constructors
  # -Wno-gnu-zero-variadic-macro-arguments
  # -Wno-documentation
  # -Wno-switch-enum
  # -Wno-missing-prototypes
  # -Wno-used-but-marked-unused
  )

set(_clang_compiler_warnings
  -Weverything
  )

set(compilerOptimizations
  -O3
  )

set(linkerOptimizations
  -O3
  )

if(CMAKE_CXX_COMPILER_ID MATCHES Clang)
  list(APPEND compilerOptimizations
    -ftree-loop-vectorize
    )
elseif(CMAKE_CXX_COMPILER_ID MATCHES GNU)
  list(APPEND compilerOptimizations
    -loop-vectorize
    -fwhole-program-vtables
    )
  list(APPEND linkerOptimizations
    -fwhole-program-vtables
    )
endif()

if(TARGET_BEAGLEBONE)
  set(beagleboneOptimizations
    -mhard-float
    -mfloat-abi=hard
    -mfpu=neon
    -mtune=cortex-a8
    )
endif()

target_compile_options(${PROJECT_NAME}
  INTERFACE
    $<$<CONFIG:Debug>: "-Og" >
    $<$<CONFIG:Release>: ${compilerOptimizations}>

    # clang/GCC warnings
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>:
    ${_clang_gcc_compiler_warnings_flag}>

    # GCC warnings
    $<$<CXX_COMPILER_ID:GNU>:${_gcc_compiler_warnings_flags}>

    # clang warnings
    $<$<CXX_COMPILER_ID:Clang>:${_clang_compiler_warnings}>

    $<$<BOOL:TARGET_BEAGLEBONE>:${beagleboneOptimizations}>
  )

target_link_options(${PROJECT_NAME}
  INTERFACE
    $<$<CONFIG:Debug>: "-O0" >
    $<$<CONFIG:Release>: ${linkerOptimizations} >
  )
