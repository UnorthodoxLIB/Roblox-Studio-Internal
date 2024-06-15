# Specify the toolchain file
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/vcpkg-toolchain.cmake" CACHE STRING "VCPKG toolchain file")

# Fallback to environment variables if not set
if(NOT DEFINED VCPKG_ROOT)
    set(VCPKG_ROOT $ENV{VCPKG_ROOT} CACHE STRING "Path to vcpkg root")
endif()

if(NOT DEFINED VCPKG_TARGET_TRIPLET)
    set(VCPKG_TARGET_TRIPLET $ENV{VCPKG_DEFAULT_TRIPLET} CACHE STRING "VCPKG target triplet")
endif()

# Print the values to debug
message(STATUS "VCPKG_ROOT: ${VCPKG_ROOT}")
message(STATUS "VCPKG_TARGET_TRIPLET: ${VCPKG_TARGET_TRIPLET}")

include("${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")

