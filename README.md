## Project structure
.
├── build                   # Compiled files
├── extern                  # Folder with dependencies
├── inc                     # Header files
├── src                     # Source files
├── tools                   # Tools and utilities
├── .gitignore
├── .gitmodules
├── CMakeLists.txt
├── LICENSE
└── README.md

## Installation

### Working with Python

In order to compile the library as a python package `pybind11` is required.
Refer to the instruction provided [here](https://pybind11.readthedocs.io/en/latest/installing.html) (use **Include as a submodule** option). As for now the steps are as follows:

```
git submodule add -b stable ../../pybind/pybind11 extern/pybind11
git submodule update --init
```

The dependencies are placed in `extern/` folder.