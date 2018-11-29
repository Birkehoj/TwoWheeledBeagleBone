cmake_minimum_required(VERSION 3.10.2 FATAL_ERROR)

project("BeagleBoneIO" LANGUAGES C CXX)

list(APPEND _sources
	src/LEDControl.cpp
	src/OnBoardButtons.cpp
)

add_library(CompilerSetup INTERFACE)

add_library("BeagleBoneIO"
	STATIC
		${_sources}
)

target_compile_features("BeagleBoneIO"
	PUBLIC cxx_std_17
)

target_compile_options("BeagleBoneIO"
	PUBLIC
	${CXX_FLAGS}
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
