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
  --suppress=missingIncludeSystem
  -I${CMAKE_SOURCE_DIR}/BeagleBoneIO/include
#  --template='{file}:{line},{severity},{id},{message}'
  --suppress=syntaxError # c++17 features not supported
  -i${CMAKE_SOURCE_DIR}/LibRobotControl/*
  -i${CMAKE_SOURCE_DIR}/LibRobotControl/include/*
#  -j5
  --xml
  -I${CMAKE_SOURCE_DIR}/LibRobotControl/library/include
  -DMAVLINK_EXTERNAL_RX_BUFFER
#  --check-config
)
