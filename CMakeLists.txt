# Minimal version of CMake
cmake_minimum_required (VERSION 2.8.12)

# Build type
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
	message(STATUS "Setting build type to 'Release' as none was specified.")
	set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
	# Set the possible values of build type for cmake-gui
	set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release")
endif ()

# Define project name
project (librply)

# The version number
set (${PROJECT_NAME}_VERSION_MAJOR 1)
set (${PROJECT_NAME}_VERSION_MINOR 1)
set (${PROJECT_NAME}_PATCH_LEVEL 4)

set (${PROJECT_NAME}_VERSION
	"${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR}")

option(LIBRPLY_BUILD_SHARED "Compile librply as a shared library" ON)
option(LIBRPLY_BUILD_STATIC "Compile librply as a static library" OFF)

option(LIBRPLY_CLANG "Use Clang Compiler" OFF)

# Clang compiler
if (LIBRPLY_CLANG)
	set (CMAKE_C_COMPILER "/usr/bin/clang")
	set (CMAKE_CC_COMPILER "/usr/bin/clang++")
endif (LIBRPLY_CLANG)

# Try to get information about using /lib/ or /lib64/
get_property(LIB64 GLOBAL PROPERTY FIND_LIBRARY_USE_LIB64_PATHS)
if ("${LIB64}" STREQUAL "TRUE")
	set(LIBSUFFIX 64)
else()
	set(LIBSUFFIX "")
endif()

set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Set output directory for libraries
set (LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib/)

# Set output directory for binaries
set (EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin/)

# Set up required subdirectory for library
add_subdirectory (src/lib)

# Set up optional subdirectory for tools
add_subdirectory (src/tools EXCLUDE_FROM_ALL)

# Add custom target for building additional tools
add_custom_target(tools)

# Make dependencies between targets
add_dependencies (tools convert create_ply dump dump_vertices sconvert)
