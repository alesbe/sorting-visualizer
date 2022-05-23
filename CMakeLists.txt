cmake_minimum_required(VERSION 3.22)
project(sorting-visualizer)

set(SFML_DIR "lib/SFML-2.5.1/lib/cmake/SFML")


find_package(SFML COMPONENTS graphics window REQUIRED)

add_executable(sorting-visualizer src/main.cpp src/Sortable.cpp src/SortAlgorithms.cpp src/SortController.cpp src/Utils.cpp)

target_link_libraries(sorting-visualizer sfml-graphics sfml-window)

