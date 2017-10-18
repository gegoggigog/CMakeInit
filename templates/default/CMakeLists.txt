project(!@project@!)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(!@project@!_VERSION 0.0.1)

add_executable(!@exec@! !@exec@!.cpp)
set_property(TARGET !@exec@! PROPERTY VERSION ${!@project@!_VERSION})

############# Installing #############
install(TARGETS !@exec@!
  RUNTIME DESTINATION bin
)
