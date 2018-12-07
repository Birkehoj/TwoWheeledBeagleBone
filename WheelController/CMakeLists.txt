cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project("WheelController" LANGUAGES C CXX)

list(APPEND _sources
	src/WheelController.cpp
)

add_library(${PROJECT_NAME}
	STATIC
		${_sources}
)

target_compile_features(${PROJECT_NAME}
	PUBLIC cxx_std_17
)

set_target_properties(${PROJECT_NAME}
	PROPERTIES
	CXX_STANARD 17
	CXX_EXTENSIONS OFF
	CXX_STANARD_REQUIRED ON
	POSITION_INDEPENDENT_CODE ON
)

target_include_directories(${PROJECT_NAME}
	PUBLIC
		./include
)

target_link_libraries(${PROJECT_NAME}
	PRIVATE
		BeagleBoneIO
)
