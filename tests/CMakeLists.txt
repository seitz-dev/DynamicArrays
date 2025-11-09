cmake_minimum_required(VERSION 4.0)

# Find Catch2
find_package(Catch2 CONFIG REQUIRED)

# Add your test source(s)
set(TEST_SOURCES
        list/list_init_tests.cpp
        list/list_insertion_tests.cpp
        list/list_init_lookup_tests.cpp
        sorting/sorting_algorithm_tests.cpp
        ../src/models/sorting/parser/ValueSortParser.cpp
)

# Create the test executable BEFORE linking or including directories
add_executable(DynamicArraysTests ${TEST_SOURCES})

# Link Catch2
target_link_libraries(DynamicArraysTests PRIVATE DynamicArraysLib Catch2::Catch2WithMain)

# Allow test code to include project headers
target_include_directories(DynamicArraysTests PRIVATE ../include)