cmake_minimum_required(VERSION 3.8)

find_package(Criterion REQUIRED)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(unit_tests
    "assert_truth.hpp"
    "4008.cpp"
    "4013.cpp"
    "builtin_gates.cpp"
    "circuit.cpp"
    "clock.cpp"
    "latches.cpp"
    "nts_gates.cpp"
    "parser.cpp"
    # "4017.cpp"
)
target_link_libraries(unit_tests nts)
target_link_libraries(unit_tests ${CRITERION_LIBRARIES})
target_include_directories(unit_tests PRIVATE ${CRITERION_INCLUDE_DIRS})
