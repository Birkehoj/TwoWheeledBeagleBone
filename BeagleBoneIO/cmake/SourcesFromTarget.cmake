function(getSourcePaths target absSourcePaths)

get_target_property(target_sources ${target} SOURCES)

foreach(target_src ${target_sources})
  get_filename_component(target_src ${target_src} ABSOLUTE)
  list(APPEND absPaths ${target_src})
endforeach()

set(absSourcePaths ${absPaths} PARENT_SCOPE)

endfunction()
