# CMakeList.txt : CMake project for NanoTekSpice, include source and define
# project specific logic here.
#
cmake_minimum_required(VERSION 3.8)

project(nts)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add source to this project's executable.
add_library(nts STATIC
    "include/nts/AComponent.hpp"
    "include/nts/AndGate.hpp"
    "include/nts/BuiltInComponentFactory.hpp"
    "include/nts/Circuit.hpp"
    "include/nts/ClockComponent.hpp"
    "include/nts/ConstComponent.hpp"
    "include/nts/IComponent.hpp"
    "include/nts/IComponentFactory.hpp"
    "include/nts/LoggerComponent.hpp"
    "include/nts/MultiComponentFactory.hpp"
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
    "src/MultiComponentFactory.cpp"
    "src/NotGate.cpp"
    "src/NtsCircuit.cpp"
    "src/NtsComponentFactory.cpp"
    "src/RomComponent.cpp"
    "src/StaticComponentFactory.cpp"
    "src/Tristate.cpp"
)
target_include_directories(nts PUBLIC "include")
