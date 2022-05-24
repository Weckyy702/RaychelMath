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
        using vec3 = basic_vec3<TestType>;

#define RAYCHEL_END_TEST }

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


TEMPLATE_TEST_CASE("Vector normalization", "[RaychelMath][Vector3]", RAYCHEL_VEC3_FLOATING_TYPES)
{
    using namespace Raychel;
    using vec3 = basic_vec3<TestType>;

    const TestType inv_sqrt_2 = 1.0 / std::sqrt(2.0);

    {
        const vec3 v = normalize(vec3{1, 0, 1});

        REQUIRE(equivalent<TestType>(v.x(), inv_sqrt_2));
        REQUIRE(equivalent<TestType>(v.y(), 0));
        REQUIRE(equivalent<TestType>(v.z(), inv_sqrt_2));
    }

    {
        const vec3 v = normalize(vec3{12, 0, 12});

        REQUIRE(equivalent(v.x(), inv_sqrt_2));
        REQUIRE(equivalent<TestType>(v.y(), 0));
        REQUIRE(equivalent(v.z(), inv_sqrt_2));
    }

}


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

    if constexpr(std::is_floating_point_v<TestType>)
    {
        const vec3 b{27, 4, 9};

        const auto d = dist(a, b);

        REQUIRE(equivalent<TestType>(d, std::sqrt(TestType(229))));
    }

RAYCHEL_END_TEST


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


    {
        const vec3 b{27, 4, 9};

        const auto d = dist_sq(a, b);

        REQUIRE(d == 229);
    }

RAYCHEL_END_TEST

TEMPLATE_TEST_CASE("Vector cross product", "[RaychelMath][Vector3]", RAYCHEL_VEC3_FLOATING_TYPES)
{
    using namespace Raychel;
    using vec3 = basic_vec3<TestType>;

    //v x 0 = 0 for any v
    {
        const vec3 v{12, -4, 7};
        const vec3 b{};

        const vec3 c = cross(v, b);

        REQUIRE(equivalent<TestType>(c.x(), 0));
        REQUIRE(equivalent<TestType>(c.y(), 0));
        REQUIRE(equivalent<TestType>(c.z(), 0));
    }

    //a || b => a x b = 0
    {
        const vec3 v{9, 123, 6};

        vec3 c = cross(v, v);

        REQUIRE(equivalent<TestType>(c.x(), 0));
        REQUIRE(equivalent<TestType>(c.y(), 0));
        REQUIRE(equivalent<TestType>(c.z(), 0));

        c = cross(v, -v);

        REQUIRE(equivalent<TestType>(c.x(), 0));
        REQUIRE(equivalent<TestType>(c.y(), 0));
        REQUIRE(equivalent<TestType>(c.z(), 0));

        c = cross(v, v * TestType(3));

        REQUIRE(equivalent<TestType>(c.x(), 0));
        REQUIRE(equivalent<TestType>(c.y(), 0));
        REQUIRE(equivalent<TestType>(c.z(), 0));
    }

    //a x b = -(b x a)
    {
        const vec3 a{-1, 12, 0};
        const vec3 b{1, 0, 2};

        const vec3 c_pos = cross(a, b);
        const vec3 c_neg = cross(b, a);

        REQUIRE(equivalent<TestType>(c_pos.x(), -c_neg[0]));
        REQUIRE(equivalent<TestType>(c_pos.y(), -c_neg[1]));
        REQUIRE(equivalent<TestType>(c_pos.z(), -c_neg[2]));
    }

    //cross product follows the right hand rule
    {
        constexpr vec3 x{1, 0, 0};
        constexpr vec3 y{0, 1, 0};
        constexpr vec3 z{0, 0, 1};

        const vec3 xy = cross(x, y);

        REQUIRE(equivalent<TestType>(xy.x(), 0));
        REQUIRE(equivalent<TestType>(xy.y(), 0));
        REQUIRE(equivalent<TestType>(xy.z(), 1));

        const vec3 xz = cross(x, z);

        REQUIRE(equivalent<TestType>(xz.x(), 0));
        REQUIRE(equivalent<TestType>(xz.y(), -1));
        REQUIRE(equivalent<TestType>(xz.z(), 0));

        const vec3 zy = cross(z, y);

        REQUIRE(equivalent<TestType>(zy.x(), -1));
        REQUIRE(equivalent<TestType>(zy.y(), 0));
        REQUIRE(equivalent<TestType>(zy.z(), 0));
    }

    //cross product follows the right hand rule, Chapter Two
    {
        const vec3 a{12, 7, -34};
        const vec3 b{7, 0, -2};

        auto res = cross(a, b);

        REQUIRE(res.x() == -14);
        REQUIRE(res.y() == -214);
        REQUIRE(res.z() == -49);

        res = cross(b, a);

        REQUIRE(res.x() == 14);
        REQUIRE(res.y() == 214);
        REQUIRE(res.z() == 49);

    }
}

#ifdef _MSC_VER
    #pragma warning ( pop )
#endif
