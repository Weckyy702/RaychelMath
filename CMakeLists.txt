cmake_minimum_required(VERSION 3.0)

option(RAYCHELMATH_BUILD_TESTS "If Unit tests should be built alongside the library. Requires Catch2" OFF)

project(RaychelMath VERSION 1.0.0)

include(cmake/find_dependencies.cmake)

add_subdirectory(src)

if(${RAYCHELMATH_BUILD_TESTS})
    message(STATUS "Adding tests")
    include(CTest)
    add_subdirectory(test)
endif()