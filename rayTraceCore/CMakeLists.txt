set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
set( CMAKE_VERBOSE_MAKEFILE on )

set(CORE_SOURCE
    ray.c
    rayhit.c
    camera.c
    ${UTIL_DIR}/vector.c
    ${UTIL_DIR}/usefulfunctions.c
    light.c
    geometry.c
    ellipsoid.c
    material.c
    triangle.c)

set(CORE_HEADER
    ${CMAKE_SOURCE_DIR}/include/rayTracerCore/ray.h
    ${CMAKE_SOURCE_DIR}/include/rayTracerCore/rayhit.h
    ${CMAKE_SOURCE_DIR}/include/rayTracerCore/light.h
    ${CMAKE_SOURCE_DIR}/include/rayTracerCore/material.h
    ${CMAKE_SOURCE_DIR}/include/rayTracerCore/shapes/geometry.h
    ${CMAKE_SOURCE_DIR}/include/rayTracerCore/shapes/ellipsoid.h
    ${CMAKE_SOURCE_DIR}/include/rayTracerCore/shapes/triangle.h
    ${UTIL_DIR_HEADERS}/vector.h
    ${UTIL_DIR_HEADERS}/usefulfunctions.h
    ${UTIL_DIR_HEADERS}/colors.h)

add_library(rayCore ${CORE_SOURCE} ${CORE_HEADER})
target_link_libraries(rayCore m)