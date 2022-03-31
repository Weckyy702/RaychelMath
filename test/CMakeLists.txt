if(NOT CATCH_2_EXTERNAL)
    find_package(Catch2 REQUIRED)
endif()
if(NOT RAYCHEL_CORE_EXTERNAL)
    find_package(RaychelCore REQUIRED)
endif()
if(NOT RAYCHEL_LOGGER_EXTERNAL)
    find_package(RaychelLogger REQUIRED)
endif()

file(GLOB_RECURSE RAYCHELMATH_TEST_SOURCES "*.test.cpp")

add_executable(RaychelMath_test
    ${RAYCHELMATH_TEST_SOURCES}
)

target_compile_features(RaychelMath_test PUBLIC cxx_std_20)

target_link_libraries(RaychelMath_test
    PUBLIC RaychelMath
    PUBLIC RaychelLogger
    PUBLIC Catch2::Catch2
)


include(Catch)
catch_discover_tests(RaychelMath_test)