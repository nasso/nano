cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(nanotekspice
    "include/Repl.hpp"
    "src/main.cpp"
    "src/Repl.cpp"
)
target_link_libraries(nanotekspice nts)
target_include_directories(nanotekspice PRIVATE "include")

add_custom_command(
	TARGET nanotekspice PRE_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		${CMAKE_SOURCE_DIR}/components
        $<TARGET_FILE_DIR:nanotekspice>/components
)
