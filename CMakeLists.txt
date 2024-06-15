cmake_minimum_required(VERSION 3.8)

# OPTIONS, IMPORTANT!

set(VCPKG_ROOT "P:/vcpkg")
set(VCPKG_TARGET_TRIPLET "x64-windows")
# Setup Compiler

set(CMAKE_CXX_COMPILER "path/to/clang++")
set(CMAKE_C_COMPILER "path/to/clang")

SET (CMAKE_C_FLAGS_INIT                "-Wall -std=c11")
SET (CMAKE_C_FLAGS_DEBUG_INIT          "-g")
SET (CMAKE_C_FLAGS_MINSIZEREL_INIT     "-Os -DNDEBUG")
SET (CMAKE_C_FLAGS_RELEASE_INIT        "-O3 -DNDEBUG")
SET (CMAKE_C_FLAGS_RELWITHDEBINFO_INIT "-O2 -g")
SET (CMAKE_CXX_FLAGS_INIT                "-Wall -std=c++17")
SET (CMAKE_CXX_FLAGS_DEBUG_INIT          "-g")
SET (CMAKE_CXX_FLAGS_MINSIZEREL_INIT     "-Os -DNDEBUG")
SET (CMAKE_CXX_FLAGS_RELEASE_INIT        "-O3 -DNDEBUG")
SET (CMAKE_CXX_FLAGS_RELWITHDEBINFO_INIT "-O2 -g")

# Project Reference.
project("RobloxStudioPatcher")

# VCPKG
include(vcpkg_installed/vcpkg-toolchain.cmake)

# VCPKG Depedencies Check
find_package(CURL REQUIRED)
#find_package(libzip CONFIG REQUIRED)

# Create Programs

# Executables
add_executable(RobloxStudioPatcher "Program/patcher.c")
add_executable(OptiStudioPatcher "Program/optipatch.c")
add_executable(SmartPatcher "Program/smartpatcher.c")
#add_executable(StudioBootstrapper "Program/RobloxStudioBootstrapper.c") THIS IS COMING LATER!

# Libraries
add_library(PatcherLib "Program/patcherlib.c")

# Apply VCPKG Dependencies
target_link_libraries(PatcherLib CURL::libcurl)
target_link_libraries(SmartPatcher CURL::libcurl)
#target_link_libraries(StudioBootstrapper PatcherLib)
#target_link_libraries(StudioBootstrapper libzip::zip)
#
#find_package(CURL REQUIRED)
#target_link_libraries(PatcherLib PRIVATE CURL::libcurl)
#