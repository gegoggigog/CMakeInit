project(!@project@!)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)

set(!@project@!_VERSION 0.0.1)

include(GenerateExportHeader)

add_library(!@lib@! SHARED !@lib@!.cpp)
generate_export_header(!@lib@!)
set_property(TARGET !@lib@! PROPERTY VERSION ${!@project@!_VERSION})
set_property(TARGET !@lib@! PROPERTY SOVERSION 3)
set_property(TARGET !@lib@! PROPERTY INTERFACE_!@lib@!_MAJOR_VERSION 3)
set_property(TARGET !@lib@! APPEND PROPERTY COMPATIBLE_INTERFACE_STRING !@lib@!_MAJOR_VERSION
)


############# Installing #############
install(TARGETS !@lib@! EXPORT !@project@!Targets
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
)
install(
  FILES
    a_header.h
    "${CMAKE_CURRENT_BINARY_DIR}/!@lib@!_export.h"
  DESTINATION
    include
  COMPONENT
    Devel
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/!@project@!/!@project@!ConfigVersion.cmake"
  VERSION ${!@project@!_VERSION}
  COMPATIBILITY AnyNewerVersion
)

export(EXPORT !@project@!Targets
  FILE "${CMAKE_CURRENT_BINARY_DIR}/!@project@!/!@project@!Targets.cmake"
  NAMESPACE !@project@!::
)
configure_file(cmake/!@project@!Config.cmake
  "${CMAKE_CURRENT_BINARY_DIR}/!@project@!/!@project@!Config.cmake"
  COPYONLY
)

set(ConfigPackageLocation lib/cmake/!@project@!)
install(EXPORT !@project@!Targets
  FILE
    !@project@!Targets.cmake
  NAMESPACE
    !@project@!::
  DESTINATION
    ${ConfigPackageLocation}
)
install(
  FILES
    "${CMAKE_CURRENT_BINARY_DIR}/!@project@!/!@project@!Config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/!@project@!/!@project@!ConfigVersion.cmake"
  DESTINATION
    ${ConfigPackageLocation}
  COMPONENT
    Devel
)
