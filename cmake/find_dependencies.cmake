include(FetchContent)

if(${RAYCHELMATH_BUILD_TESTS})
    find_package(Catch2 QUIET)

    if(NOT Catch2_FOUND)

        message(STATUS "Could not find a local installation of Catch2, downloading one off github...")

        FetchContent_Declare(CATCH_2
            GIT_REPOSITORY "https://github.com/catchorg/Catch2"
            GIT_TAG "v2.13.6"
        )

        FetchContent_MakeAvailable(CATCH_2)

        set(CATCH_2_EXTERNAL true)
        set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${Catch2_SOURCE_DIR}/contrib)

    endif()
endif()

find_package(RaychelCore QUIET)

if(NOT RaychelCore_FOUND)

    message(STATUS "Could not find a local installation of RaychelCore, downloading one off github...")

    FetchContent_Declare(RAYCHEL_CORE
        GIT_REPOSITORY "https://github.com/Weckyy702/RaychelCore"
        GIT_TAG "main"
    )

    FetchContent_MakeAvailable(RAYCHEL_CORE)

    set(RAYCHEL_CORE_EXTERNAL true)

endif()

find_file(GSL_MAIN_INCLUDE "gsl/gsl")
if(NOT GSL_MAIN_INCLUDE)
    message(STATUS "Could not find a local installation of the GSL, downloading one off github...")

    FetchContent_Declare(GSL
        GIT_REPOSITORY "https://github.com/microsoft/GSL"
        GIT_TAG "v3.1.0"
    )

    FetchContent_MakeAvailable(GSL)

    set(GSL_EXTERNAL true)
endif()