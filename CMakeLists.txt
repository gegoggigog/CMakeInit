cmake_minimum_required(VERSION 3.7.1)
project(CMakeInit)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMakeInit_VERSION 0.0.1)

add_executable(cmake-init src/cmake-init.cpp)
set_property(TARGET cmake-init PROPERTY VERSION ${CMakeInit_VERSION})

# TODO: Add needed std requirements, std::experimental::filesystem etc.

############# Installing #############
install(TARGETS cmake-init
  RUNTIME DESTINATION bin
)

install(DIRECTORY templates DESTINATION .)
