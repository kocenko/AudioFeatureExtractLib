cmake_minimum_required(VERSION 3.12)
project(mfcc_pkg)

# Include headers
include_directories(${CMAKE_SOURCE_DIR}/inc)

# Add PyBind11
add_subdirectory(${CMAKE_SOURCE_DIR}/extern/pybind11)

# Set output directories
set(OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/libs)
file(MAKE_DIRECTORY ${OUTPUT_DIRECTORY})

# Python Wrapper
pybind11_add_module(mfcc_python ${CMAKE_SOURCE_DIR}/src/python_wrapper.cpp ${CMAKE_SOURCE_DIR}/src/mfcc.cpp)

# C# wrapper
add_library(mfcc_csharp SHARED ${CMAKE_SOURCE_DIR}/src/csharp_wrapper.cpp ${CMAKE_SOURCE_DIR}/src/mfcc.cpp)

# Custom target to move the files
add_custom_target(post_build ALL
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:mfcc_python> ${OUTPUT_DIRECTORY}
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:mfcc_csharp> ${OUTPUT_DIRECTORY}
    DEPENDS mfcc_python mfcc_csharp
    COMMENT "Copying output files to ${OUTPUT_DIRECTORY}."
)
