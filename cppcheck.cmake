# additional target to perform cppcheck run, requires cppcheck

add_custom_target(
		cppcheck
		COMMAND /usr/bin/cppcheck
		--enable=all
		--std=c++14
		--verbose
		--quiet
		--std=c++14
		--enable=warning
		--inconclusive
		--force
		--inline-suppr
		--language=c++
		--verbose
		--check-config
		--quiet
		--library=std.cfg
		--suppress=missingIncludeSystem
		-I${CMAKE_SOURCE_DIR}/BeagleBoneIO/include
#		-j5
#		--xml
		${CMAKE_SOURCE_DIR}
)
