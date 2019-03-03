cmake_minimum_required(VERSION 3.13)

target_sources(${LIBRARY_TARGET_NAME}
  PRIVATE
    # Headers
    # This relative path is really no ideal, TODO: prityfy
    ../include/BeagleBoneIO/EncoderEqep.h
    ../include/BeagleBoneIO/LEDControl.h
    ../include/BeagleBoneIO/MotorsController.h
    ../include/BeagleBoneIO/OnBoardButtons.h
  # Sources
    EncoderEqep.cpp
    LEDControl.cpp
    MotorsController.cpp
    OnBoardButtons.cpp
  )
