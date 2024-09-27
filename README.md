## Project structure

```
.
├── build                   # Compiled files
├── extern                  # Folder with dependencies
├── inc                     # Header files
├── src                     # Source files
├── .gitignore
├── .gitmodules
├── CMakeLists.txt
├── LICENSE
└── README.md
```

## Installation

### Working with Python

In order to compile the library as a python package `pybind11` is required.
Refer to the instruction provided [here](https://pybind11.readthedocs.io/en/latest/installing.html) (use **Include as a submodule** option). As for now the steps are as follows:

```
git submodule add -b stable ../../pybind/pybind11 extern/pybind11
git submodule update --init
```

Notice: The dependencies are placed in `extern/` folder. In CMakeLists.txt it is included in the line `add_subdirectory(${CMAKE_SOURCE_DIR}/extern/pybind11)`.

When the package is installed you can use the following commands to compile the project:

1. Create `build/` and `libs/` folders if they do not exist: `mkdir build`, `mkdir libs`
2. Go to this folder: `cd build`
3. Run cmake: `cmake ..`
4. Compile the package: `cmake --build . --config Release`

After that the python package should appear in the folder `libs/` with the appropriate `.pyd` extension.

IMPORTANT NOTE: The library has to be compiled with the same version of Python as the target program's version.

### Working with C#

1. Create `build/` and `libs/` folders if they do not exist: `mkdir build`, `mkdir libs`
2. Go to this folder: `cd build`
3. Run cmake: `cmake ..`
4. Compile the package: `cmake --build . --config Release`

After that the C library should appear in the folder `libs/` with the appropriate `.dll` extension.


### Input handling

Inputs provided to the feature extractor have to match the shape defined in the `inc/config.h` file.
Providing data with different shape than expected can cause the program using this library to crash.
For now, the responsibility of delivering inputs with appropriate dimensions is on the side of the program using the library.
