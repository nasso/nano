# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required(VERSION 3.8)

project(tekspice)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# My Template Library
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/mtl)

# The NanoTekSpice engine library
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/nano)

# Native CLI/REPL
if(NOT EMSCRIPTEN)
	add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/cli)
endif()
