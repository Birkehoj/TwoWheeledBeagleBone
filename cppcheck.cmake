# additional target to perform cppcheck run, requires cppcheck

add_custom_target(
  cppcheck
  COMMAND cppcheck
  ${CMAKE_SOURCE_DIR}/BeagleBoneIO
  --enable=all
  --std=c++14
  --verbose
  --quiet
  --enable=warning
  --inconclusive
  --force
  --inline-suppr
  --language=c++
  --verbose
  -j5
  --suppress=unusedFunction
  -I${CMAKE_SOURCE_DIR}/BeagleBoneIO/include
  -i${CMAKE_SOURCE_DIR}/ExternalDependencies/LibRobotControl/*
  -I${CMAKE_SOURCE_DIR}/ExternalDependencies/LibRobotControl/LibRobotControl/library/include
  -DMAVLINK_EXTERNAL_RX_BUFFER
#  --xml
#  --check-config

#  --template='{file}:{line},{severity},{id},{message}'
#  --suppress=syntaxError # c++17 features not supported # Unmatched suppression
#  --suppress=missingIncludeSystem # Unmatched suppression
)
