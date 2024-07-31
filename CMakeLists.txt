cmake_minimum_required(VERSION 3.12)
project(mfcc_pkg)

# Include headers
include_directories(${CMAKE_SOURCE_DIR}/inc)

# Add PyBind11
add_subdirectory(${CMAKE_SOURCE_DIR}/extern/pybind11)

# Add source files
pybind11_add_module(mfcc ${CMAKE_SOURCE_DIR}/src/mfcc.cpp ${CMAKE_SOURCE_DIR}/src/mfcc_wrapper.cpp)
