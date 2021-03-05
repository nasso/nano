cmake_minimum_required(VERSION 3.8)

find_package(Criterion REQUIRED)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(unit_tests
    "4008.cpp"
    "4013.cpp"
    "4017.cpp"
    "4040.cpp"
    "4514.cpp"
    "assert_truth.hpp"
    "builtin_gates.cpp"
    "circuit.cpp"
    "latches.cpp"
    "logger.cpp"
    "nts_gates.cpp"
    "nts_utils.cpp"
    "nts_utils.hpp"
    "parser.cpp"
    "rom.cpp"
)
target_link_libraries(unit_tests nts)
target_link_libraries(unit_tests ${CRITERION_LIBRARIES})
target_include_directories(unit_tests PRIVATE ${CRITERION_INCLUDE_DIRS})

add_custom_command(
	TARGET unit_tests POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		${CMAKE_SOURCE_DIR}/components $<TARGET_FILE_DIR:unit_tests>/components
)
