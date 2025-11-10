# DynamicArrays Distribution Guide

## Building the Distribution Package

### Option 1: Using PowerShell (Recommended)
```powershell
./build-dist.ps1
```

### Option 2: Using Batch
```cmd
build-dist.bat
```

### Option 3: Manual CMake Commands
```powershell
# Create build directory
mkdir build
cd build

# Configure for Release
cmake -G "Visual Studio 17 2022" -DCMAKE_BUILD_TYPE=Release ..

# Build
cmake --build . --config Release

# Create packages
cpack -C Release

cd ..
```

## Output Files

After building, the `build/` directory will contain:
- **DynamicArrays-1.0.0-Windows.zip** - ZIP archive (all platforms)
- **DynamicArrays-1.0.0-Windows.exe** - NSIS installer (Windows only)

## Installation from Package

### From ZIP Archive
```powershell
# Extract the ZIP file
Expand-Archive DynamicArrays-1.0.0-Windows.zip -DestinationPath "C:\Program Files\DynamicArrays"
```

### From NSIS Installer
Simply run the `.exe` installer and follow the GUI prompts.

### Manual Installation from Build
```powershell
cd build
cmake --install . --prefix "C:\Program Files\DynamicArrays"
```

## Using in Your Projects

### Method 1: CMake find_package (Recommended)
After installation, add to your `CMakeLists.txt`:
```cmake
find_package(DynamicArrays REQUIRED)

add_executable(myapp main.cpp)
target_link_libraries(myapp PRIVATE DynamicArrays::DynamicArraysLib)
```

### Method 2: Header-Only Usage
Simply include the headers:
```cpp
#include <DynamicArrays/models/List.h>
```

## Cross-Platform Distribution

The current setup supports:
- **Windows**: ZIP + NSIS installer
- **Linux**: TGZ + DEB package (change generator in CMakeLists.txt)
- **macOS**: TGZ package

To build for different platforms, modify the `CPACK_GENERATOR` in `CMakeLists.txt`.

## Version Management

Update the version in `CMakeLists.txt`:
```cmake
project(DynamicArrays VERSION 1.0.1 LANGUAGES CXX)
```

This automatically updates all distribution packages.

## Publishing

### GitHub Releases
1. Create a new release tag
2. Upload the generated ZIP and EXE files
3. Include build notes and changelog

### Package Managers (vcpkg, Conan, etc.)
Create a portfile.cmake (for vcpkg) or conanfile.py (for Conan) using this distribution as a base.
