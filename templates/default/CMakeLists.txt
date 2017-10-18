cmake_minimum_required(VERSION 3.7.1)
project(!@project@!)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(!@project@!_VERSION 0.0.1)

add_executable(!@exec@! src/!@exec@!.cpp)
set_property(TARGET !@exec@! PROPERTY VERSION ${!@project@!_VERSION})

############# Installing #############
install(TARGETS !@exec@!
  RUNTIME DESTINATION bin
)
