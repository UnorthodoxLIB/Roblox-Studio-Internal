cmake_minimum_required(VERSION 3.8)

<<<<<<< HEAD
#Settings (Set properly!)
set(VCPKG_PATH "P:/vcpkg")

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# Project Reference.
project("RobloxStudioPatcher")

# VCPKG Setup.
set(STATIC_VCPKG_INCLUDE_PATH "${VCPKG_PATH}/installed/x64-windows-static/include")
set(CMAKE_TOOLCHAIN_FILE "${VCPKG_PATH}/scripts/buildsystems/vcpkg.cmake")

message(STATUS "VCPKG: ${VCPKG_PATH}")
message(STATUS "VCPKGINC: ${STATIC_VCPKG_INCLUDE_PATH}")
message(STATUS "TOOLCHAIN: ${CMAKE_TOOLCHAIN_FILE}")
=======
# VCPKG OPTIONS
set(VCPKG_ROOT "P:/vcpkg")
set(VCPKG_TARGET_TRIPLET "x64-windows")

# Setup Compiler
set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_C_COMPILER "clang")

set(CMAKE_C_FLAGS_INIT                  "-Wall -std=c11")
set(CMAKE_C_FLAGS_DEBUG_INIT            "-g")
set(CMAKE_C_FLAGS_MINSIZEREL_INIT       "-Os -DNDEBUG")
set(CMAKE_C_FLAGS_RELEASE_INIT          "-O3 -DNDEBUG")
set(CMAKE_C_FLAGS_RELWITHDEBINFO_INIT   "-O2 -g")
set(CMAKE_CXX_FLAGS_INIT                "-Wall -std=c++17")
set(CMAKE_CXX_FLAGS_DEBUG_INIT          "-g")
set(CMAKE_CXX_FLAGS_MINSIZEREL_INIT     "-Os -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE_INIT        "-O3 -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO_INIT "-O2 -g")

set(CMAKE_BUILD_RPATH                   "${workspaceFolder}/out/build")

# Setup Project
project("RobloxStudioPatcher")

# Clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Setup VCPKG
set(VCPKG_LIBRARY_LINKAGE static)
include(vcpkg_installed/vcpkg-toolchain.cmake)

# VCPKG Dependencies Check
find_package(CURL REQUIRED)

# Detect architecture
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(ARCH_SUFFIX "64x")
else()
    set(ARCH_SUFFIX "32x")
endif()

# Define the output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${workspaceFolder}/out/build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${workspaceFolder}/out/build)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${workspaceFolder}/out/build)

# Create Programs with architecture suffix
add_executable(RobloxStudioPatcher${ARCH_SUFFIX} "Program/patcher.c")
add_executable(OptiStudioPatcher${ARCH_SUFFIX} "Program/optipatch.c")
add_executable(SmartPatcher${ARCH_SUFFIX} "Program/smartpatcher.c")
>>>>>>> ec172efb65ad64322f94a32342619ac1e81f427d

# Libraries
add_library(PatcherLib "Program/patcherlib.c")

<<<<<<< HEAD
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET RobloxStudioPatcher PROPERTY CXX_STANDARD 20)
endif()
=======
# Apply VCPKG Dependencies
target_link_libraries(PatcherLib CURL::libcurl)
target_link_libraries(SmartPatcher${ARCH_SUFFIX} CURL::libcurl)

# Link PatcherLib to executables
target_link_libraries(RobloxStudioPatcher${ARCH_SUFFIX} PatcherLib)
target_link_libraries(OptiStudioPatcher${ARCH_SUFFIX} PatcherLib)
>>>>>>> ec172efb65ad64322f94a32342619ac1e81f427d

# Set output directories for all targets
set_target_properties(RobloxStudioPatcher${ARCH_SUFFIX} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set_target_properties(OptiStudioPatcher${ARCH_SUFFIX} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set_target_properties(SmartPatcher${ARCH_SUFFIX} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set_target_properties(PatcherLib PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
