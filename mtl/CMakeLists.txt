cmake_minimum_required(VERSION 3.8)

project(mtl)
include(CTest)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(sources
    "include/mtl/Option.hpp"
)

add_library(mtl INTERFACE)
target_include_directories(mtl INTERFACE "include")

if(NOT EMSCRIPTEN AND BUILD_TESTING)
    find_package(Criterion REQUIRED)

    add_executable(mtl_unit_tests
        "tests/option.cpp"
    )
    target_link_libraries(mtl_unit_tests mtl)
    target_link_libraries(mtl_unit_tests ${CRITERION_LIBRARIES})
    target_include_directories(mtl_unit_tests PRIVATE ${CRITERION_INCLUDE_DIRS})

    add_test(
        NAME mtl_tests_build
        COMMAND "${CMAKE_COMMAND}"
                --build "${CMAKE_BINARY_DIR}"
                --config "$<CONFIG>"
                --target mtl_unit_tests
    )
    set_tests_properties(mtl_tests_build
        PROPERTIES FIXTURES_SETUP mtl_tests_fixture)

    add_test(NAME mtl_tests COMMAND mtl_unit_tests)
    set_tests_properties(mtl_tests
        PROPERTIES FIXTURES_REQUIRED mtl_tests_fixture)
endif()
