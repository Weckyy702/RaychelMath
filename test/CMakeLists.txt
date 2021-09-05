find_package(Catch2 CONFIG REQUIRED)
find_package(RaychelLogger REQUIRED)


file(GLOB_RECURSE RAYCHELMATH_TEST_SOURCES "*.test.cpp")

add_executable(Unit_test
    ${RAYCHELMATH_TEST_SOURCES}
)

target_compile_features(Unit_test PUBLIC cxx_std_20)

target_link_libraries(Unit_test
    PUBLIC RaychelMath
    PUBLIC RaychelLogger
    PUBLIC Catch2::Catch2
)


include(Catch)
catch_discover_tests(Unit_test)