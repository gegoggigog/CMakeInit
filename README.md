# Usage
Assuming `cmake-init` is in path:
```sh
$ cmake-init [-G<template>] [-D<opt>=<val> ...]
```
If no template is specified it will use the `default` template. If no option is specified it will use the defaults specified in `cmake_init_defaults.txt` in the corresponding template folder.
# Installation
Use `CMake`.

# Notes
Only tested on `Windows` with `Visual Studio 15 2017`. Uses `std::experimental::filesystem`.