cmake_minimum_required(VERSION 3.12)
project(mfcc_pkg)

# Include headers
include_directories(${CMAKE_SOURCE_DIR}/inc)

# Add PyBind11
add_subdirectory(${CMAKE_SOURCE_DIR}/extern/pybind11)


# Python Wrapper
pybind11_add_module(mfcc_python ${CMAKE_SOURCE_DIR}/src/python_wrapper.cpp ${CMAKE_SOURCE_DIR}/src/mfcc.cpp)


# C# wrapper
add_library(mfcc_csharp SHARED ${CMAKE_SOURCE_DIR}/src/csharp_wrapper.cpp ${CMAKE_SOURCE_DIR}/src/mfcc.cpp)
