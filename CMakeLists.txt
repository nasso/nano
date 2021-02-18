# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required(VERSION 3.8)

project("tekspice")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

option(ENABLE_TESTS "Build tests along with the library" ON)

# Include sub-projects.
add_subdirectory("nts")
add_subdirectory("cli")

if (ENABLE_TESTS)
	enable_testing()
	add_subdirectory("tests")
endif ()

install(TARGETS nanotekspice)
