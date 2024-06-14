cmake_minimum_required(VERSION 3.8)

# Setup Compiler
C_COMPILER_ID("clang")
CXX_COMPILER_ID("clang++")

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

# Packages.
find_package(CURL CONFIG REQUIRED)

# Create Programs
add_executable(RobloxStudioPatcher "Program/patcher.c")
add_executable(OptiStudioPatcher "Program/optipatch.c")
add_executable(SmartPatcher "Program/smartpatcher.c")
add_library(PatcherLib "Program/patcherlib.c")