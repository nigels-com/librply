# Source code for verse library
set (librply_src rply.c)

include_directories (./)

# Make build flags compiler specific for libverse.so
if (CMAKE_COMPILER_IS_GNUCC)
    set (CMAKE_C_FLAGS "-fPIC -Wall -Wextra -pedantic -Wno-long-long")
	if (CMAKE_BUILD_TYPE STREQUAL "Debug")
		set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ggdb -O0")
	elseif( CMAKE_BUILD_TYPE STREQUAL "Release" )
		set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DNDEBUG -O3 -fno-strict-aliasing")
	endif ()
endif (CMAKE_COMPILER_IS_GNUCC)

# Set up shared verse library (libverse.so)
if (LIBRPLY_BUILD_SHARED)
	add_library (librply_shared_lib SHARED ${librply_src})
	set_target_properties (librply_shared_lib PROPERTIES
		VERSION "${${PROJECT_NAME}_VERSION}"
		SOVERSION "${${PROJECT_NAME}_VERSION}.${${PROJECT_NAME}_PATCH_LEVEL}"
		OUTPUT_NAME "rply"
		clean_direct_output 1)

	# The rule to install shared library used by Verse server and Verse clients
	install (TARGETS librply_shared_lib
		LIBRARY
		DESTINATION lib${LIBSUFFIX})
endif()

# Static library
if (LIBRPLY_BUILD_STATIC)
	add_library (librply_static_lib STATIC ${librply_src})
	set_target_properties (librply_static_lib PROPERTIES
		VERSION "${${PROJECT_NAME}_VERSION}"
		SOVERSION "${${PROJECT_NAME}_VERSION}.${${PROJECT_NAME}_PATCH_LEVEL}"
		OUTPUT_NAME "rply"
		clean_direct_output 1)

	install (TARGETS librply_static_lib
		LIBRARY
		DESTINATION lib${LIBSUFFIX})
endif()

# Install rply.h file
install (FILES "${PROJECT_SOURCE_DIR}/src/lib/rply.h"
	DESTINATION include)
