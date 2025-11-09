cmake_minimum_required(VERSION 4.0)
project(DynamicArrays)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(DynamicArraysLib
        src/models/List.cpp
        src/models/sorting/SortAlgorithm.cpp
        src/models/sorting/parser/ValueSortParser.cpp
        src/models/sorting/parser/IntSortParser.cpp
        src/models/sorting/BubbleSortAlgorithm.cpp
        src/models/sorting/SelectionSortAlgorithm.cpp
        include/models/sorting/SelectionSortAlgorithm.h
)

target_include_directories(DynamicArraysLib PUBLIC include)

add_executable(DynamicArrays main.cpp)
target_link_libraries(DynamicArrays PRIVATE DynamicArraysLib)

add_subdirectory(tests)
