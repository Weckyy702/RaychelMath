#include <type_traits>
#include "catch2/catch.hpp"

#include "RaychelMath/equivalent.h"
#include "RaychelMath/vec2.h"
#include "RaychelMath/constants.h"

//clang-format doesn't like these macros
// clang-format off

#ifdef _MSC_VER
    #pragma warning( push )
    #pragma warning (disable : 4244 4305) //MSVC's warnings about narrowing conversion are nice to have, but not this time
#endif

#define RAYCHEL_VEC2_TEST_TYPES int, size_t, float, double, long double
#define RAYCHEL_VEC2_FLOATING_TYPES float, double, long double

#define RAYCHEL_BEGIN_TEST(test_name, test_tag)                                \
    TEMPLATE_TEST_CASE(test_name, test_tag, RAYCHEL_VEC2_TEST_TYPES)           \
    {                                                                          \
        using namespace Raychel;                                               \
        using vec2 = vec2<TestType>;

#define RAYCHEL_END_TEST }

RAYCHEL_BEGIN_TEST("vec2 dot product", "[RaychelMath][Vector2]")

    const vec2 v1{1, 2};
    const vec2 v2{4, 5};

    const auto d = dot(v1, v2);

    REQUIRE(d == 14);

RAYCHEL_END_TEST

RAYCHEL_BEGIN_TEST("vec2 magnitude", "[RaychelMath][Vector2]")

    //the zero vector has magnitude 0
    REQUIRE(mag(vec2{}) == 0);

    //the orthonormal basis vector have magnitude 1
    REQUIRE(mag(vec2{1, 0}) == 1);
    REQUIRE(mag(vec2{0, 1}) == 1);

    //Pythagoras holds
    REQUIRE(mag(vec2{3, 4}) == 5);
    REQUIRE(mag(vec2{9, 40}) == 41);

    //And the same for squared distances

    REQUIRE(mag_sq(vec2{}) == 0);

    REQUIRE(mag_sq(vec2{1, 0}) == 1);
    REQUIRE(mag_sq(vec2{0, 1}) == 1);

    REQUIRE(mag_sq(vec2{3, 4}) == 25);
    REQUIRE(mag_sq(vec2{9, 40}) == 1681);

RAYCHEL_END_TEST

TEMPLATE_TEST_CASE("vec2 normalization", "[RaychelMath][Vector2]", RAYCHEL_VEC2_FLOATING_TYPES)
{
    using namespace Raychel;
    using vec2 = vec2<TestType>;

    const TestType inv_sqrt_2 = 1.0 / std::sqrt(2.0);

    {
        const vec2 v = normalize(vec2{1, 1});

        REQUIRE(v[0] == Approx(inv_sqrt_2));
        REQUIRE(v[1] == Approx(inv_sqrt_2));
    }
}

RAYCHEL_BEGIN_TEST("vec2 distance", "[RaychelMath][Vector2]")
    const vec2 v{15, 29};

    {
        const vec2 b{};

        REQUIRE(dist(v, b) == mag(v));
    }

    {
        const vec2 b{12, 25};

        REQUIRE(dist(v, b) == 5);
    }

    //And the same for squared distances

    {
        const vec2 b{};

        REQUIRE(dist_sq(v, b) == mag_sq(v));
    }

    {
        const vec2 b{12, 25};

        REQUIRE(dist_sq(v, b) == 25);
    }

RAYCHEL_END_TEST

TEMPLATE_TEST_CASE("vec2 rotation", "[RaychelMath][Vector2]", RAYCHEL_VEC2_FLOATING_TYPES)
{
    using vec2 = Raychel::vec2<TestType>;
    constexpr auto pi = Raychel::pi<TestType>;
    constexpr auto half_pi = Raychel::half_pi<TestType>;

    {
        const vec2 v{1, 0};
        const auto v2 = rotate(v, 0);

        REQUIRE(v2 == v);
    }

    {
        const vec2 v{1, 0};
        const auto v2 = rotate(v, pi);

        REQUIRE(v2[0] == -1);
        REQUIRE(Raychel::equivalent<TestType>(v2[1], 0));
    }

    {
        const vec2 v{1, 0};
        const auto v2 = rotate(v, half_pi);

        REQUIRE(Raychel::equivalent<TestType>(v2[0], 0));
        REQUIRE(v2[1] == 1);
    }
}
// clang-format on