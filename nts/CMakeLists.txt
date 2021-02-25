# CMakeList.txt : CMake project for NanoTekSpice, include source and define
# project specific logic here.
#
cmake_minimum_required(VERSION 3.8)

project(nts)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add source to this project's executable.
add_library(nts STATIC
    "include/AComponent.hpp"
    "include/AndGate.hpp"
    # "include/BuiltInComponentFactory.hpp"
    "include/Circuit.hpp"
    "include/ClockComponent.hpp"
    "include/ConstComponent.hpp"
    "include/IComponent.hpp"
    # "include/IComponentFactory.hpp"
    # "include/IInputComponent.hpp"
    # "include/InputComponent.hpp"
    # "include/IOutputComponent.hpp"
    # "include/IPinComponent.hpp"
    # "include/MainCircuit.hpp"
    # "include/MultiComponentFactory.hpp"
    "include/NotGate.hpp"
    # "include/NTSCircuit.hpp"
    # "include/NTSComponentFactory.hpp"
    # "include/OutputComponent.hpp"
    "include/Tristate.hpp"
    "src/AComponent.cpp"
    "src/AndGate.cpp"
    # "src/BuiltInComponentFactory.cpp"
    "src/ClockComponent.cpp"
    "src/ConstComponent.cpp"
    "src/IComponent.cpp"
    # "src/InputComponent.cpp"
    # "src/MainCircuit.cpp"
    # "src/MultiComponentFactory.cpp"
    "src/NotGate.cpp"
    # "src/NTSCircuit.cpp"
    # "src/NTSComponentFactory.cpp"
    # "src/OutputComponent.cpp"
    "src/Tristate.cpp"
)
target_include_directories(nts PUBLIC "include")
