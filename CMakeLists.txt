cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project("TwoWheeledBeagleBone" LANGUAGES C CXX)

link_libraries("-static") # This seems like a hack

add_subdirectory("LibRobotControl/library")
add_subdirectory("BeagleBoneIO")
add_subdirectory("WheelController")
add_subdirectory("TwoWheeledRobot")
