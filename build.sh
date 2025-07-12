#!/usr/bin/env bash
set -e

# Prompt if no build type is passed
if [ -z "$1" ]; then
    echo "Select a build type:"
    select opt in Debug Release RelWithDebInfo MinSizeRel Frontend; do
        if [[ -n "$opt" ]]; then
            BUILD_TYPE=$opt
            break
        else
            echo "Invalid option"
        fi
    done
else
    BUILD_TYPE=$1
fi

BUILD_SUBDIR="build/$(echo "$BUILD_TYPE" | tr '[:upper:]' '[:lower:]')-script-built"

echo "Building in ${BUILD_TYPE} mode under ${BUILD_SUBDIR}..."

# Create build directory
mkdir -p "$BUILD_SUBDIR"
cd "$BUILD_SUBDIR"

# Run cmake with compile_commands support
cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ../..

# Build frontend target first
cmake --build . --target frontend

# Build full program unless Frontend-only
if [ "$BUILD_TYPE" != "Frontend" ]; then
    cmake --build . --config $BUILD_TYPE
fi

cd ../..

# Symlink compile_commands.json
ln -sf "$BUILD_SUBDIR/compile_commands.json" compile_commands.json

echo "Build complete."

