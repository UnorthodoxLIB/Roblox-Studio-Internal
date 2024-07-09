cmake_minimum_required(VERSION 3.8)

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

# Create Programs
add_executable(RobloxStudioPatcher "Program/patcher.c")
add_executable(OptiStudioPatcher "Program/optipatch.c")
add_executable(SmartPatcher "Program/smartpatcher.c")
add_library(PatcherLib "Program/patcherlib.c")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET RobloxStudioPatcher PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
