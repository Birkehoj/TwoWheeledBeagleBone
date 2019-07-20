cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

# additional target to perform cppcheck run, requires cppcheck
include(ProcessorCount)
ProcessorCount(N)

set(clangTidyBin "clang-tidy-8")

find_path(clangTidyPath ${clangTidyBin})
if(clangTidyPath)
  message("Found clang-tidy at: ${clangTidyPath}")
else()
  find_path(clangTidyPath clang-tidy)
  message("Unable to find desired clang-tidy version falling back to system default.")
endif()

if(clangTidyPath)
  set(clanTidyPath "${clangTidyPath}/${clangTidyBin}")
  add_custom_target(
    run-clang-tidy
    COMMAND run-clang-tidy
    -j ${N}
    -p ${CMAKE_BINARY_DIR}
    -header-filter='.*'
  #  -quiet
    -clang-tidy-binary ${clangTidyPath}
  )
else()
  message("Clang-tidy check not possible due to missing clang-tidy installation")
endif()
