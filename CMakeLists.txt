cmake_minimum_required(VERSION 2.8)
project(RayTracer)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -std=gnu99")
set( CMAKE_VERBOSE_MAKEFILE ON )
set(UTIL_DIR ${CMAKE_SOURCE_DIR}/util)
set(UTIL_DIR_HEADERS ${CMAKE_SOURCE_DIR}/include/util)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMakeModules)
option(BUILDCOLORS "Build color output" ON)
if(BUILDCOLORS)
    add_definitions(-DCOLORS)
endif(BUILDCOLORS)
include_directories(include)
add_subdirectory(rayTraceCore)

# --- ImageMagick (recommended, optional) ---
# ImageMagick 6.7.5-5 is recommended for colorspaces to be handled correctly.

# IVS - installed version is too old.
set(CMAKE_LIBRARY_PATH "/research/kuhl/public-vrlab/ImageMagick-6.8.9-5/magick/.libs/" ${CMAKE_LIBRARY_PATH})
set(CMAKE_INCLUDE_PATH "/research/kuhl/public-vrlab/ImageMagick-6.8.9-5/" ${CMAKE_INCLUDE_PATH})
# CCSR - installed version is too old.
set(CMAKE_LIBRARY_PATH "/home/kuhl/public-vrlab/ImageMagick-6.8.9-6/magick/.libs/" ${CMAKE_LIBRARY_PATH})
set(CMAKE_INCLUDE_PATH "/home/kuhl/public-vrlab/ImageMagick-6.8.9-6/" ${CMAKE_INCLUDE_PATH})

find_package(ImageMagick COMPONENTS MagickCore)


if(ImageMagick_FOUND)
	include_directories(${ImageMagick_INCLUDE_DIRS})
endif()


set(HEADER_FILES
    ${UTIL_DIR_HEADERS}/vector.h
    ${UTIL_DIR_HEADERS}/colors.h
    ${UTIL_DIR_HEADERS}/ringbuffer.h
    ${UTIL_DIR_HEADERS}/usefulfunctions.h
    ${UTIL_DIR_HEADERS}/imageio.h
    include/rayTracerCore/ray.h
    include/rayTracerCore/camera.h
    include/rayTracerCore/shapes/geometry.h
    include/rayTracerCore/shapes/ellipsoid.h
    include/rayTracerCore/shapes/triangle.h
    include/rayTracerCore/material.h)


set(SOURCE_FILES main.c ${UTIL_DIR}/vector.c ${UTIL_DIR}/usefulfunctions.c ${UTIL_DIR}/ringbuffer.c ${UTIL_DIR}/imageio.c)
add_executable(raytrace ${SOURCE_FILES} ${HEADER_FILES})

if(ImageMagick_FOUND)
		target_link_libraries(raytrace m rayCore ${ImageMagick_LIBRARIES})
else()
	message(WARNING "ImageMagick library not found, not compiling: ${NEED_IM}")
endif()
