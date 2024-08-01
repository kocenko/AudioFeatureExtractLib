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

1. Create `build/` folder if it does not exist: `mkdir build`
2. Go to this folder: `cd build`
3. Run cmake: `cmake ..`
4. Compile the package: `cmake --build . --config Release`

After that the python package should appear in the folder `build\Release\` with the appropriate `.pyd` extension, e.g. `build\Release\mfcc.cp311-win_amd64.pyd`.

### Working with C#

