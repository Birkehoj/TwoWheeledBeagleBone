set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR ARM)

if(MINGW OR CYGWIN OR WIN32)
    set(UTIL_SEARCH_CMD where)
elseif(UNIX OR APPLE)
    set(UTIL_SEARCH_CMD which)
endif()

set(TOOLCHAIN_PREFIX arm-linux-gnueabihf-)
set(TOOLCHAIN_TRIPLE arm-linux-gnueabihf)

execute_process(
        COMMAND ${UTIL_SEARCH_CMD} ${TOOLCHAIN_PREFIX}gcc-8
        OUTPUT_VARIABLE BINUTILS_PATH
        OUTPUT_STRIP_TRAILING_WHITESPACE
)

message(STATUS "Binary utils path = ${BINUTILS_PATH}")

get_filename_component(ARM_TOOLCHAIN_DIR ${BINUTILS_PATH} DIRECTORY)

set(triple ${TOOLCHAIN_TRIPLE})

set(CMAKE_ASM_COMPILER ${TOOLCHAIN_PREFIX}gcc-8)
set(CMAKE_C_COMPILER clang-8)
set(CMAKE_C_COMPILER_TARGET ${triple})
set(CMAKE_CXX_COMPILER clang++-8)
set(CMAKE_CXX_COMPILER_TARGET ${triple})

set(CMAKE_C_FLAGS_INIT "-B${ARM_TOOLCHAIN_DIR}")
set(CMAKE_CXX_FLAGS_INIT "-B${ARM_TOOLCHAIN_DIR}")

#set(CMAKE_C_FLAGS_ ${beagleboneOptimizations})
#set(CMAKE_CXX_FLAGS ${beagleboneOptimizations})
# only for successful compilation of CMake test
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
# provide clang with ARM GCC toolchain include directory info
include_directories(
  /usr/${TOOLCHAIN_TRIPLE}/include
  /usr/${TOOLCHAIN_TRIPLE}/include/c++/8/arm-linux-gnueabihf
  )

message(STATUS /usr/${TOOLCHAIN_TRIPLE}/include)

set(CMAKE_OBJCOPY ${ARM_TOOLCHAIN_DIR}/${TOOLCHAIN_PREFIX}objcopy CACHE INTERNAL "objcopy tool")
set(CMAKE_SIZE_UTIL ${ARM_TOOLCHAIN_DIR}/${TOOLCHAIN_PREFIX}size CACHE INTERNAL "size tool")

set(CMAKE_FIND_ROOT_PATH ${ARM_TOOLCHAIN_DIR})
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)


set(TARGET_BEAGLEBONE ON)
