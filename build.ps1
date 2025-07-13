$ErrorActionPreference = "Stop"

# Prompt for build type if not passed
if ($args.Count -lt 1) {
    Write-Host "Select a build type:"
    $choices = @("Debug", "Release", "RelWithDebInfo", "MinSizeRel", "Frontend")
    for ($i = 0; $i -lt $choices.Count; $i++) {
        Write-Host "$($i + 1)): $($choices[$i])"
    }

    do {
        $selection = Read-Host "Enter choice number"
        $buildType = $choices[$selection - 1]
    } while (-not $buildType)
} else {
    $buildType = $args[0]
}

$buildSubdir = "build/$($buildType.ToLower())-script-built"

Write-Host "Building in $buildType mode under $buildSubdir..."

# Create build dir
if (-not (Test-Path -Path $buildSubdir)) {
    New-Item -ItemType Directory -Path $buildSubdir | Out-Null
}

Push-Location $buildSubdir

# Run CMake config
cmake -DCMAKE_BUILD_TYPE=$buildType -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ../..

# Build frontend target first
cmake --build . --target frontend

# Build full program unless Frontend-only
if ($buildType -ne "Frontend") {
    cmake --build . --config $buildType
}

Pop-Location

# Copy compile_commands.json to root
Copy-Item -Path "$buildSubdir/compile_commands.json" -Destination "compile_commands.json" -Force

Write-Host "Build complete."

