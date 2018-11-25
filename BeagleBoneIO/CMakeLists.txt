cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project("BeagleBoneIO" LANGUAGES C CXX)

list(APPEND _sources
	src/LEDControl.cpp
)

add_library("BeagleBoneIO"
	STATIC
		${_sources}
)

target_compile_features("BeagleBoneIO"
	PUBLIC cxx_std_17
)

set_target_properties("BeagleBoneIO"
	PROPERTIES
	CXX_STANARD 17
	CXX_EXTENSIONS OFF
	CXX_STANARD_REQUIRED ON
	POSITION_INDEPENDENT_CODE ON
)

target_include_directories("BeagleBoneIO"
	PUBLIC
		./include
)

target_link_libraries("BeagleBoneIO"
	PRIVATE
		robotics_cape
)
