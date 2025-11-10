@echo off
REM Build and Package DynamicArrays Distribution

echo ============================================================
echo Building DynamicArrays Distribution
echo ============================================================

REM Create build directory
if not exist "build" mkdir build
cd build

REM Configure with CMake
echo.
echo [1/3] Configuring CMake...
cmake -G "Visual Studio 17 2022" -DCMAKE_BUILD_TYPE=Release ..
if errorlevel 1 (
    echo CMake configuration failed!
    exit /b 1
)

REM Build the project
echo.
echo [2/3] Building project...
cmake --build . --config Release
if errorlevel 1 (
    echo Build failed!
    exit /b 1
)

REM Create distribution package
echo.
echo [3/3] Creating distribution packages...
cpack -C Release
if errorlevel 1 (
    echo Packaging failed!
    exit /b 1
)

echo.
echo ============================================================
echo Build complete!
echo Distribution packages created in: build\
echo ============================================================
cd ..
pause
