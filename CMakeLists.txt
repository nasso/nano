# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required(VERSION 3.8)

project("tekspice")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# The NanoTekSpice engine library
add_subdirectory(nts)

if(NOT EMSCRIPTEN)
	option(ENABLE_TESTS "Build tests along with the library" ON)

	# Native CLI/REPL
	add_subdirectory(cli)

	# Unit tests for native
	if(ENABLE_TESTS)
		enable_testing()
		add_subdirectory(tests)
	endif()
endif()
