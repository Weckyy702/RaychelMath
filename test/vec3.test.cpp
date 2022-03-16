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

#define RAYCHEL_VEC3_TEST_TYPES int, size_t, float, double, long double
#define RAYCHEL_VEC3_FLOATING_TYPES float, double, long double

#define RAYCHEL_BEGIN_TEST(test_name, test_tag)                                \
    TEMPLATE_TEST_CASE(test_name, test_tag, RAYCHEL_VEC3_TEST_TYPES)           \
    {                                                                          \
        using namespace Raychel;                                               \
        using vec3 = vec3<TestType>;

#define RAYCHEL_END_TEST }

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
RAYCHEL_BEGIN_TEST("Creating vectors", "[RaychelMath][Vector3]")

    const vec3 v{};
    const vec3 v1{12};
    const vec3 v2{5, 200};
    const vec3 v3{5, 100, 12};

    REQUIRE(v[0] == 0);
    REQUIRE(v[1] == 0);
    REQUIRE(v[2] == 0);

    REQUIRE(v1[0] == 12);
    REQUIRE(v1[1] == 0);
    REQUIRE(v1[2] == 0);

    REQUIRE(v2[0] == 5);
    REQUIRE(v2[1] == 200);
    REQUIRE(v2[2] == 0);

    REQUIRE(v3[0] == 5);
    REQUIRE(v3[1] == 100);
    REQUIRE(v3[2] == 12);

RAYCHEL_END_TEST

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
RAYCHEL_BEGIN_TEST("Vector addition", "[RaychelMath][Vector3]")

    vec3 v{12, 13, 4};

    const vec3 res = v + vec3{1, 12, 9};

    REQUIRE(res[0] == 13);
    REQUIRE(res[1] == 25);
    REQUIRE(res[2] == 13);

    v += vec3{1, 7, 12};

    REQUIRE(v[0] == 13);
    REQUIRE(v[1] == 20);
    REQUIRE(v[2] == 16);

RAYCHEL_END_TEST

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
RAYCHEL_BEGIN_TEST("Vector subtraction", "[RaychelMath][Vector3]")

    vec3 v{7, 500, 9};

    const vec3 res = v - vec3{7, 12, 8};

    REQUIRE(res[0] == 0);
    REQUIRE(res[1] == 488);
    REQUIRE(res[2] == 1);


    v -= res;

    REQUIRE(v[0] == 7);
    REQUIRE(v[1] == 12);
    REQUIRE(v[2] == 8);

    if constexpr (std::is_signed_v<TestType>) {

        const vec3 v2 = -v;

        REQUIRE(v2[0] == -7);
        REQUIRE(v2[1] == -12);
        REQUIRE(v2[2] == -8);

    }

RAYCHEL_END_TEST

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
RAYCHEL_BEGIN_TEST("Vector comparison: equality", "[RaychelMath][Vector3]")

    const vec3 v{12, 7, 9};
    const vec3 v2{};

    REQUIRE(v == v);
    REQUIRE(v == vec3{12, 7, 9});
    REQUIRE(v != vec3{12, 0, 4 });

RAYCHEL_END_TEST

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
RAYCHEL_BEGIN_TEST("Vector dot product", "[RaychelMath][Vector3]")

    const vec3 a{0, 1, 0};
    //v * v == |v|²
    {
        const vec3 b{0, 1, 0};
        const auto d = dot(a, b);

        REQUIRE(d == 1);
    }

    //a * b == 0 => a and b are orthogonal
    {
        const vec3 b{1, 0, 0};
        const auto d = dot(a, b);

        REQUIRE(d == 0);
    }

    //a * b == -1 * |a| * |b| => a and b point in different directions
    if constexpr(!std::is_unsigned<TestType>::value)
    {
        const vec3 b{0, -1, 0};
        const auto d = dot(a, b);

        REQUIRE(d == -1);
    }

    //a * b = cos(theta)
    if constexpr(std::is_floating_point_v<TestType>)
    {
        const vec3 b = vec3(std::sqrt(2.0), std::sqrt(2.0), 0);

        const auto d = dot(a, b);

        REQUIRE(equivalent<TestType>(d, std::sqrt(2.0)));
    }

    //v * 0 = 0
    REQUIRE(dot(vec3{}, vec3{12, 400, 7}) == 0);

    //v * v = |v|²
    const vec3 v{12, 45, 9};
    REQUIRE(dot(v, v) == 2'250);

RAYCHEL_END_TEST

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
RAYCHEL_BEGIN_TEST("Vector magnitude", "[RaychelMath][Vector3]")

    //the zero vector has magnitude 0
    REQUIRE(mag(vec3{}) == 0);

    //the orthonormal basis vectors have magnitude 1
    REQUIRE(mag(vec3{1, 0, 0}) == 1);
    REQUIRE(mag(vec3{0, 1, 0}) == 1);
    REQUIRE(mag(vec3{0, 0, 1}) == 1);

    //Pythagoras holds
    REQUIRE(mag(vec3{1, 2, 2}) == 3);
    REQUIRE(mag(vec3{12, 15, 16}) == 25);

    if constexpr (std::is_floating_point_v<TestType>)
    {
        REQUIRE(mag(vec3{1, 0, 1}) == std::sqrt(TestType(2.0)));

        const vec3 v{std::sqrt(TestType(2)), 0, std::sqrt(TestType(2))};
        const auto m = mag(v);
        REQUIRE(equivalent<TestType>(m, 2));
    }


    REQUIRE(mag_sq(vec3{}) == 0);

    REQUIRE(mag_sq(vec3{1, 0, 0}) == 1);
    REQUIRE(mag_sq(vec3{0, 1, 0}) == 1);
    REQUIRE(mag_sq(vec3{0, 0, 1}) == 1);

    REQUIRE(mag_sq(vec3{4, 17, 12}) == 449);

RAYCHEL_END_TEST

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
TEMPLATE_TEST_CASE("Vector normalization", "[RaychelMath][Vector3]", RAYCHEL_VEC3_FLOATING_TYPES)
{
    using namespace Raychel;
    using vec3 = vec3<TestType>;

    const TestType inv_sqrt_2 = 1.0 / std::sqrt(2.0);

    {
        const vec3 v = normalize(vec3{1, 0, 1});

        REQUIRE(equivalent<TestType>(v[0], inv_sqrt_2));
        REQUIRE(equivalent<TestType>(v[1], 0));
        REQUIRE(equivalent<TestType>(v[2], inv_sqrt_2));
    }

    {
        const vec3 v = normalize(vec3{12, 0, 12});

        REQUIRE(equivalent(v[0], inv_sqrt_2));
        REQUIRE(equivalent<TestType>(v[1], 0));
        REQUIRE(equivalent(v[2], inv_sqrt_2));
    }

}

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
RAYCHEL_BEGIN_TEST("Vector distance", "[RaychelMath][Vector3]")

    const vec3 a{12, 4, 7};

    {
        const vec3 b{};

        const auto d = dist(a, b);

        REQUIRE(d == mag(a));
    }

    {
        const vec3 b{10, 1, 1};

        const auto d = dist(a, b);

        REQUIRE(d == 7);
    }

    if constexpr (std::is_signed_v<TestType>)
    {
        const vec3 b{0, -12, 28};

        const auto d = dist(a, b);

        REQUIRE(d == 29);
    }

    //NOLINTEXTLINE: clang-tidy gets really confused by these ifs
    if constexpr(std::is_floating_point_v<TestType>)
    {
        const vec3 b{27, 4, 9};

        const auto d = dist(a, b);

        REQUIRE(equivalent<TestType>(d, std::sqrt(TestType(229))));
    }

RAYCHEL_END_TEST

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
RAYCHEL_BEGIN_TEST("Vector squared distance", "[RaychelMath][Vector3]")

    const vec3 a{12, 4, 7};

    {
        const vec3 b{};

        const auto d = dist_sq(a, b);

        REQUIRE(d == mag_sq(a));
    }

    {
        const vec3 b{10, 1, 1};

        const auto d = dist_sq(a, b);

        REQUIRE(d == 49);
    }

    if constexpr (std::is_signed_v<TestType>)
    {
        const vec3 b{0, -12, 28};

        const auto d = dist_sq(a, b);

        REQUIRE(d == 841);
    }

    //NOLINTNEXTLINE: clang-tidy doesn't like this file :(
    {
        const vec3 b{27, 4, 9};

        const auto d = dist_sq(a, b);

        REQUIRE(d == 229);
    }

RAYCHEL_END_TEST

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
TEMPLATE_TEST_CASE("Vector cross product", "[RaychelMath][Vector3]", RAYCHEL_VEC3_FLOATING_TYPES)
{
    using namespace Raychel;
    using vec3 = vec3<TestType>;

    //v x 0 = 0 for any v
    {
        const vec3 v{12, -4, 7};
        const vec3 b{};

        const vec3 c = cross(v, b);

        REQUIRE(equivalent<TestType>(c[0], 0));
        REQUIRE(equivalent<TestType>(c[1], 0));
        REQUIRE(equivalent<TestType>(c[2], 0));
    }

    //a || b => a x b = 0
    {
        const vec3 v{9, 123, 6};

        vec3 c = cross(v, v);

        REQUIRE(equivalent<TestType>(c[0], 0));
        REQUIRE(equivalent<TestType>(c[1], 0));
        REQUIRE(equivalent<TestType>(c[2], 0));

        c = cross(v, -v);

        REQUIRE(equivalent<TestType>(c[0], 0));
        REQUIRE(equivalent<TestType>(c[1], 0));
        REQUIRE(equivalent<TestType>(c[2], 0));

        c = cross(v, v * TestType(3));

        REQUIRE(equivalent<TestType>(c[0], 0));
        REQUIRE(equivalent<TestType>(c[1], 0));
        REQUIRE(equivalent<TestType>(c[2], 0));
    }

    //a x b = -(b x a)
    {
        const vec3 a{-1, 12, 0};
        const vec3 b{1, 0, 2};

        const vec3 c_pos = cross(a, b);
        const vec3 c_neg = cross(b, a);

        REQUIRE(equivalent<TestType>(c_pos[0], -c_neg[0]));
        REQUIRE(equivalent<TestType>(c_pos[1], -c_neg[1]));
        REQUIRE(equivalent<TestType>(c_pos[2], -c_neg[2]));
    }

    //cross product follows the right hand rule
    {
        constexpr vec3 x{1, 0, 0};
        constexpr vec3 y{0, 1, 0};
        constexpr vec3 z{0, 0, 1};

        const vec3 xy = cross(x, y);

        REQUIRE(equivalent<TestType>(xy[0], 0));
        REQUIRE(equivalent<TestType>(xy[1], 0));
        REQUIRE(equivalent<TestType>(xy[2], 1));

        const vec3 xz = cross(x, z);

        REQUIRE(equivalent<TestType>(xz[0], 0));
        REQUIRE(equivalent<TestType>(xz[1], -1));
        REQUIRE(equivalent<TestType>(xz[2], 0));

        const vec3 zy = cross(z, y);

        REQUIRE(equivalent<TestType>(zy[0], -1));
        REQUIRE(equivalent<TestType>(zy[1], 0));
        REQUIRE(equivalent<TestType>(zy[2], 0));
    }

    //cross product follows the right hand rule, Chapter Two
    {
        const vec3 a{12, 7, -34};
        const vec3 b{7, 0, -2};

        auto res = cross(a, b);

        REQUIRE(res[0] == -14);
        REQUIRE(res[1] == -214);
        REQUIRE(res[2] == -49);

        res = cross(b, a);

        REQUIRE(res[0] == 14);
        REQUIRE(res[1] == 214);
        REQUIRE(res[2] == 49);
    }
}

#ifdef _MSC_VER
    #pragma warning ( pop )
#endif