# CMakeList.txt : CMake project for NanoTekSpice, include source and define
# project specific logic here.
#
cmake_minimum_required(VERSION 3.8)

project(nts)
include(CTest)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(sources
    "include/nts/AComponent.hpp"
    "include/nts/AndGate.hpp"
    "include/nts/BuiltInComponentFactory.hpp"
    "include/nts/Circuit.hpp"
    "include/nts/ComboComponentFactory.hpp"
    "include/nts/ConstComponent.hpp"
    "include/nts/IComponent.hpp"
    "include/nts/IComponentFactory.hpp"
    "include/nts/LoggerComponent.hpp"
    "include/nts/NotGate.hpp"
    "include/nts/NtsCircuit.hpp"
    "include/nts/NtsComponentFactory.hpp"
    "include/nts/Pinout.hpp"
    "include/nts/RomComponent.hpp"
    "include/nts/StaticComponentFactory.hpp"
    "include/nts/Tristate.hpp"
    "src/AComponent.cpp"
    "src/AndGate.cpp"
    "src/BuiltInComponentFactory.cpp"
    "src/Circuit.cpp"
    "src/ComboComponentFactory.cpp"
    "src/ConstComponent.cpp"
    "src/IComponent.cpp"
    "src/IComponentFactory.cpp"
    "src/LoggerComponent.cpp"
    "src/NotGate.cpp"
    "src/NtsCircuit.cpp"
    "src/NtsComponentFactory.cpp"
    "src/Pinout.cpp"
    "src/RomComponent.cpp"
    "src/StaticComponentFactory.cpp"
    "src/Tristate.cpp"
)

set(libs mtl)

if(EMSCRIPTEN)
    # When targeting WebAssembly, the library is a standalone module
    add_executable(nts ${sources})
    target_link_libraries(nts ${libs})
    target_include_directories(nts PRIVATE "include")
    target_link_options(nts PRIVATE
        "--bind"
        "-sENVIRONMENT=web"
        "-sMODULARIZE=1"
        "-sEXPORT_NAME=createNts"
        "-sEXPORT_ES6=1"
        "-sDISABLE_EXCEPTION_CATCHING=1"
        "-sINCOMING_MODULE_JS_API=['locateFile']"
        "-sINVOKE_RUN=0"
        "-sAUTO_JS_LIBRARIES=0"
        "-sAUTO_NATIVE_LIBRARIES=0"
        "-sSTRICT_JS=1"
        "--no-entry")
else()
    # For native platforms, the library is statically linked
    add_library(nts STATIC ${sources})
    target_link_libraries(nts ${libs})
    target_include_directories(nts PUBLIC "include")

	# Unit tests for native
	if(BUILD_TESTING)
        find_package(Criterion REQUIRED)

        add_executable(nano_unit_tests
            "tests/4008.cpp"
            "tests/4013.cpp"
            "tests/4017.cpp"
            "tests/4040.cpp"
            "tests/assert_truth.hpp"
            "tests/builtin_gates.cpp"
            "tests/circuit.cpp"
            "tests/latches.cpp"
            "tests/logger.cpp"
            "tests/nts_gates.cpp"
            "tests/nts_utils.cpp"
            "tests/nts_utils.hpp"
            "tests/parser.cpp"
            "tests/rom.cpp"
        )
        target_link_libraries(nano_unit_tests nts)
        target_link_libraries(nano_unit_tests ${CRITERION_LIBRARIES})
        target_include_directories(nano_unit_tests PRIVATE
            ${CRITERION_INCLUDE_DIRS})

        add_test(
            NAME nts_tests_build
            COMMAND "${CMAKE_COMMAND}"
                    --build "${CMAKE_BINARY_DIR}"
                    --config "$<CONFIG>"
                    --target nano_unit_tests
        )
        set_tests_properties(nts_tests_build
            PROPERTIES FIXTURES_SETUP nts_tests_fixture)

        add_test(NAME nts_tests COMMAND nano_unit_tests)
        set_tests_properties(nts_tests PROPERTIES
            FIXTURES_REQUIRED nts_tests_fixture
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
	endif()
endif()
