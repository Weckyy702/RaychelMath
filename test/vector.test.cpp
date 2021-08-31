#include <type_traits>
#include "catch2/catch.hpp"

#include "RaychelMath/Impl/vec3Impl.inl"
#include "RaychelMath/Impl/vectorImpl.inl"
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
    using vec3 = vec3Imp<TestType>;

    const vec3 v{4, 1, 0};
    const vec3 v2{4, 1, 2};

    vec3 r = rotateX(v, pi_v<TestType>);
    REQUIRE(equivalent<TestType>(r.x, 4));
    REQUIRE(equivalent<TestType>(r.y, -1));
    REQUIRE(equivalent<TestType>(r.z, 0));

    r = rotateX(v2, half_pi<TestType>);
    REQUIRE(equivalent<TestType>(r.x, 4));
    REQUIRE(equivalent<TestType>(r.y, -2));
    REQUIRE(equivalent<TestType>(r.z, 1));


    const vec3 v3{12, 7, 9};
    const TestType theta = 1.2;
    const vec3 r_pos = rotateX(v3, theta);
    const vec3 r_neg = rotateX(v3, theta - 10*pi_v<TestType>);

    REQUIRE(equivalent<TestType>(r_pos.x, r_neg.x));
    REQUIRE(equivalent<TestType>(r_pos.y, r_neg.y));
    REQUIRE(equivalent<TestType>(r_pos.z, r_neg.z));
}

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
TEMPLATE_TEST_CASE("Vector rotation: y", "[RaychelMath][Vector3]", RAYCHEL_VEC3_FLOATING_TYPES)
{
    using namespace Raychel;
    using vec3 = vec3Imp<TestType>;

    const vec3 v{1, 4, 0};
    const vec3 v2{4, 1 ,2};

    vec3 r = rotateY(v, pi_v<TestType>);
    REQUIRE(equivalent<TestType>(r.x, -1));
    REQUIRE(equivalent<TestType>(r.y, 4));
    REQUIRE(equivalent<TestType>(r.z, 0));

    r = rotateY(v2, half_pi<TestType>);
    REQUIRE(equivalent<TestType>(r.x, 2));
    REQUIRE(equivalent<TestType>(r.y, 1));
    REQUIRE(equivalent<TestType>(r.z, -4));


    const vec3 v3{12, 7, 9};
    const TestType theta = 1.2;
    const vec3 r_pos = rotateY(v3, theta);
    const vec3 r_neg = rotateY(v3, theta - 10*pi_v<TestType>);

    REQUIRE(equivalent<TestType>(r_pos.x, r_neg.x));
    REQUIRE(equivalent<TestType>(r_pos.y, r_neg.y));
    REQUIRE(equivalent<TestType>(r_pos.z, r_neg.z));
}

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
TEMPLATE_TEST_CASE("Vector rotation: z", "[RaychelMath][Vector3]", RAYCHEL_VEC3_FLOATING_TYPES)
{
    using namespace Raychel;
    using vec3 = vec3Imp<TestType>;

    const vec3 v{1, 4, 0};
    const vec3 v2{4, 1 ,2};

    vec3 r = rotateZ(v, pi_v<TestType>);
    REQUIRE(equivalent<TestType>(r.x, -1));
    REQUIRE(equivalent<TestType>(r.y, -4));
    REQUIRE(equivalent<TestType>(r.z, 0));

    r = rotateZ(v2, half_pi<TestType>);

    REQUIRE(equivalent<TestType>(r.x, -1));
    REQUIRE(equivalent<TestType>(r.y, 4));
    REQUIRE(equivalent<TestType>(r.z, 2));

    


    const vec3 v3{12, 7, 9};
    const TestType theta = 1.2;
    const vec3 r_pos = rotateZ(v3, theta);
    const vec3 r_neg = rotateZ(v3, theta - 10*pi_v<TestType>);

    REQUIRE(equivalent<TestType>(r_pos.x, r_neg.x));
    REQUIRE(equivalent<TestType>(r_pos.y, r_neg.y));
    REQUIRE(equivalent<TestType>(r_pos.z, r_neg.z));
}

#ifdef _MSC_VER
    #pragma warning ( pop )
#endif