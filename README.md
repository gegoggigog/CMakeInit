# Usage
Assuming `cmake-init` is in path:
```
$ mkdir SomeProject
$ cd SomeProject
$ cmake-init [-G<template>] [-D<opt>=<val> ...]
```
If no template is specified it will use the `default` template. If no option is specified it will use the defaults specified in `cmake_init_defaults.txt` in the corresponding template folder. The `opt=val` pair simply do a regex to replace all occurences of `!@opt@!` in the templates with `val`. For more info, check out the templates themselves or wait until I have made a proper `--help` command.
# Installation
Example (VS):
```
$ cmake .. -DCMAKE_INSTALL_PREFIX=<install_dir>
$ cmake --build . --target INSTALL --config Release
```
# Notes
Only tested on `Windows` with `Visual Studio 15 2017`. Uses `std::experimental::filesystem`.
