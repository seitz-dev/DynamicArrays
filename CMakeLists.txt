cmake_minimum_required(VERSION 3.20)
project(DynamicArrays VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(DynamicArraysLib
        src/models/List.cpp
        include/models/List.h
        src/models/sorting/SortAlgorithm.cpp
        src/models/sorting/parser/ValueSortParser.cpp
        src/models/sorting/parser/IntSortParser.cpp
        src/models/sorting/BubbleSortAlgorithm.cpp
        src/models/sorting/SelectionSortAlgorithm.cpp
        include/models/sorting/SelectionSortAlgorithm.h
        src/models/sorting/InsertionSortAlgorithm.cpp
        include/models/sorting/InsertionSortAlgorithm.h
)

target_include_directories(DynamicArraysLib PUBLIC include)

add_executable(DynamicArrays main.cpp)
target_link_libraries(DynamicArrays PRIVATE DynamicArraysLib)

add_subdirectory(tests)

# ============================================================================
# Installation and Distribution Configuration
# ============================================================================

# Install library targets
install(TARGETS DynamicArraysLib
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin)

# Install headers
install(DIRECTORY include/ DESTINATION include/DynamicArrays)

# Install documentation
install(FILES README.md LICENSE DESTINATION docs)

# Create and install CMake config files for consumers
include(CMakePackageConfigHelpers)

configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/DynamicArraysConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/DynamicArraysConfig.cmake
    INSTALL_DESTINATION lib/cmake/DynamicArrays
)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/DynamicArraysConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/DynamicArraysConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/DynamicArraysConfigVersion.cmake
    DESTINATION lib/cmake/DynamicArrays
)

# ============================================================================
# CPack Configuration for Distribution Packages
# ============================================================================

set(CPACK_PACKAGE_NAME "DynamicArrays")
set(CPACK_PACKAGE_VENDOR "seitz-dev")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "High-performance C++20 dynamic array library")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")

# Windows-specific packaging
if(WIN32)
    set(CPACK_GENERATOR "ZIP;NSIS")
    set(CPACK_NSIS_DISPLAY_NAME "DynamicArrays Library")
else()
    set(CPACK_GENERATOR "TGZ;DEB")
    set(CPACK_DEBIAN_PACKAGE_MAINTAINER "seitz-dev")
endif()

set(CPACK_PACKAGE_FILE_NAME "DynamicArrays-${PROJECT_VERSION}-${CMAKE_SYSTEM_NAME}")
set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY OFF)

include(CPack)