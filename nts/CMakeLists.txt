# CMakeList.txt : CMake project for NanoTekSpice, include source and define
# project specific logic here.
#
cmake_minimum_required(VERSION 3.8)

project(nts)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(sources
    "include/nts/AComponent.hpp"
    "include/nts/AndGate.hpp"
    "include/nts/BuiltInComponentFactory.hpp"
    "include/nts/Circuit.hpp"
    "include/nts/ClockComponent.hpp"
    "include/nts/ConstComponent.hpp"
    "include/nts/IComponent.hpp"
    "include/nts/IComponentFactory.hpp"
    "include/nts/LoggerComponent.hpp"
    "include/nts/ComboComponentFactory.hpp"
    "include/nts/NotGate.hpp"
    "include/nts/NtsCircuit.hpp"
    "include/nts/NtsComponentFactory.hpp"
    "include/nts/RomComponent.hpp"
    "include/nts/StaticComponentFactory.hpp"
    "include/nts/Tristate.hpp"
    "src/AComponent.cpp"
    "src/AndGate.cpp"
    "src/BuiltInComponentFactory.cpp"
    "src/ClockComponent.cpp"
    "src/ConstComponent.cpp"
    "src/IComponent.cpp"
    "src/LoggerComponent.cpp"
    "src/ComboComponentFactory.cpp"
    "src/NotGate.cpp"
    "src/NtsCircuit.cpp"
    "src/NtsComponentFactory.cpp"
    "src/RomComponent.cpp"
    "src/StaticComponentFactory.cpp"
    "src/Tristate.cpp"
)

if(EMSCRIPTEN)
    # When targeting WebAssembly, the library is a standalone module
    add_executable(nts ${sources})
    target_include_directories(nts PRIVATE "include")
    target_link_options(nts PRIVATE
        "-sENVIRONMENT=web"
        "-sMODULARIZE=1"
        "-sEXPORT_NAME=createNts"
        "-sEXPORT_ES6=1"
        "-sDISABLE_EXCEPTION_CATCHING=1"
        "-sINCOMING_MODULE_JS_API=[]"
        "-sINVOKE_RUN=0"
        "-sAUTO_JS_LIBRARIES=0"
        "-sAUTO_NATIVE_LIBRARIES=0"
        "-sSTRICT_JS=1"
        "--no-entry")
else()
    # For native platforms, the library is statically linked
    add_library(nts STATIC ${sources})
    target_include_directories(nts PUBLIC "include")
endif()
