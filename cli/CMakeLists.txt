cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(nanotekspice "src/main.cpp" "src/Repl.cpp" "include/Relp.hpp")
target_link_libraries(nanotekspice nts)
target_include_directories(nanotekspice PRIVATE "include")
