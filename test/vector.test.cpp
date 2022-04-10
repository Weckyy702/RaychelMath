#include <type_traits>
#include "catch2/catch.hpp"

#include "RaychelMath/equivalent.h"
#include "RaychelMath/vec3.h"
#include "RaychelMath/vector.h"

//clang-format doesn't like these macros
// clang-format off

#ifdef _MSC_VER
    #pragma warning( push )
    #pragma warning (disable : 4244 4305) //MSVC's warnings about narrowing conversion are nice to have, but not this time
#endif

#define RAYCHEL_VEC3_FLOATING_TYPES float, double, long double

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
TEMPLATE_TEST_CASE("Vector rotate: x", "[RaychelMath][Vector3]", RAYCHEL_VEC3_FLOATING_TYPES)
{
    using namespace Raychel;
    using vec3 = basic_vec3<TestType>;

    const vec3 v{4, 1, 0};
    const vec3 v2{4, 1, 2};

    vec3 r = rotate_x(v, pi_v<TestType>);
    REQUIRE(equivalent<TestType>(r[0], 4));
    REQUIRE(equivalent<TestType>(r[1], -1));
    REQUIRE(equivalent<TestType>(r[2], 0));

    r = rotate_x(v2, half_pi<TestType>);
    REQUIRE(equivalent<TestType>(r[0], 4));
    REQUIRE(equivalent<TestType>(r[1], -2));
    REQUIRE(equivalent<TestType>(r[2], 1));


    const vec3 v3{12, 7, 9};
    const TestType theta = 1.2;
    const vec3 r_pos = rotate_x(v3, theta);
    const vec3 r_neg = rotate_x(v3, theta - 10*pi_v<TestType>);

    REQUIRE(equivalent<TestType>(r_pos[0], r_neg[0]));
    REQUIRE(equivalent<TestType>(r_pos[1], r_neg[1]));
    REQUIRE(equivalent<TestType>(r_pos[2], r_neg[2]));
}

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
TEMPLATE_TEST_CASE("Vector rotation: y", "[RaychelMath][Vector3]", RAYCHEL_VEC3_FLOATING_TYPES)
{
    using namespace Raychel;
    using vec3 = basic_vec3<TestType>;

    const vec3 v{1, 4, 0};
    const vec3 v2{4, 1 ,2};

    vec3 r = rotate_y(v, pi_v<TestType>);
    REQUIRE(equivalent<TestType>(r[0], -1));
    REQUIRE(equivalent<TestType>(r[1], 4));
    REQUIRE(equivalent<TestType>(r[2], 0));

    r = rotate_y(v2, half_pi<TestType>);
    REQUIRE(equivalent<TestType>(r[0], 2));
    REQUIRE(equivalent<TestType>(r[1], 1));
    REQUIRE(equivalent<TestType>(r[2], -4));


    const vec3 v3{12, 7, 9};
    const TestType theta = 1.2;
    const vec3 r_pos = rotate_y(v3, theta);
    const vec3 r_neg = rotate_y(v3, theta - 10*pi_v<TestType>);

    REQUIRE(equivalent<TestType>(r_pos[0], r_neg[0]));
    REQUIRE(equivalent<TestType>(r_pos[1], r_neg[1]));
    REQUIRE(equivalent<TestType>(r_pos[2], r_neg[2]));
}

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
TEMPLATE_TEST_CASE("Vector rotation: z", "[RaychelMath][Vector3]", RAYCHEL_VEC3_FLOATING_TYPES)
{
    using namespace Raychel;
    using vec3 = basic_vec3<TestType>;

    const vec3 v{1, 4, 0};
    const vec3 v2{4, 1 ,2};

    vec3 r = rotate_z(v, pi_v<TestType>);
    REQUIRE(equivalent<TestType>(r[0], -1));
    REQUIRE(equivalent<TestType>(r[1], -4));
    REQUIRE(equivalent<TestType>(r[2], 0));

    r = rotate_z(v2, half_pi<TestType>);

    REQUIRE(equivalent<TestType>(r[0], -1));
    REQUIRE(equivalent<TestType>(r[1], 4));
    REQUIRE(equivalent<TestType>(r[2], 2));




    const vec3 v3{12, 7, 9};
    const TestType theta = 1.2;
    const vec3 r_pos = rotate_z(v3, theta);
    const vec3 r_neg = rotate_z(v3, theta - 10*pi_v<TestType>);

    REQUIRE(equivalent<TestType>(r_pos[0], r_neg[0]));
    REQUIRE(equivalent<TestType>(r_pos[1], r_neg[1]));
    REQUIRE(equivalent<TestType>(r_pos[2], r_neg[2]));
}

#ifdef _MSC_VER
    #pragma warning ( pop )
#endif
