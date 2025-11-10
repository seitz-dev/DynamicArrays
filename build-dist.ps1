# Build and Package DynamicArrays Distribution Script

Write-Host "============================================================" -ForegroundColor Cyan
Write-Host "Building DynamicArrays Distribution" -ForegroundColor Cyan
Write-Host "============================================================" -ForegroundColor Cyan

# Create build directory
if (-not (Test-Path "build")) {
    New-Item -ItemType Directory -Path "build" | Out-Null
}

Set-Location build

# Step 1: Configure with CMake
Write-Host "`n[1/3] Configuring CMake..." -ForegroundColor Yellow
cmake -G "Visual Studio 17 2022" -DCMAKE_BUILD_TYPE=Release ..
if ($LASTEXITCODE -ne 0) {
    Write-Host "CMake configuration failed!" -ForegroundColor Red
    exit 1
}

# Step 2: Build the project
Write-Host "`n[2/3] Building project..." -ForegroundColor Yellow
cmake --build . --config Release
if ($LASTEXITCODE -ne 0) {
    Write-Host "Build failed!" -ForegroundColor Red
    exit 1
}

# Step 3: Create distribution package
Write-Host "`n[3/3] Creating distribution packages..." -ForegroundColor Yellow
cpack -C Release
if ($LASTEXITCODE -ne 0) {
    Write-Host "Packaging failed!" -ForegroundColor Red
    exit 1
}

Write-Host "`n============================================================" -ForegroundColor Green
Write-Host "Build complete!" -ForegroundColor Green
Write-Host "Distribution packages created in: build/" -ForegroundColor Green
Write-Host "============================================================" -ForegroundColor Green

Set-Location ..
