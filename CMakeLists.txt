cmake_minimum_required(VERSION 3.22)
project(sorting-visualizer)

set(default_build_type "Release")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message( STATUS "Setting build type to '${default_build_type}' as none was specified.")
  set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
    "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

set(SFML_DIR "C:/Program Files (x86)/SFML/lib/cmake/SFML")

find_package(SFML COMPONENTS graphics window CONFIG REQUIRED)

add_executable(sorting-visualizer src/main.cpp src/Sortable.cpp src/SortAlgorithms.cpp src/SortController.cpp src/Utils.cpp)

target_link_libraries(sorting-visualizer sfml-graphics sfml-window)

# Copy across .dlls for windows users
get_target_property(SFML_TYPE sfml-graphics TYPE)
if(SFML_TYPE STREQUAL "SHARED_LIBRARY")
  message(STATUS "Copying sfml-graphics DLLs to ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>")
  add_custom_command(
  TARGET sorting-visualizer POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy
  $<TARGET_FILE:sfml-graphics>
  ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>)
  
  message(STATUS "Copying sfml-window DLLs to ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>")  
  add_custom_command(
  TARGET sorting-visualizer POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy
  $<TARGET_FILE:sfml-window>
  ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>)
  
  message(STATUS "Copying sfml-system DLLs to ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>")  
  add_custom_command(
  TARGET sorting-visualizer POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy
  $<TARGET_FILE:sfml-system>
  ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>)
endif()

