#include "RaychelMath/Tuple.h"

#include "catch2/catch.hpp"

#define RAYCHEL_TUPLE_TEST_TYPES int, size_t, float, double, long double

#define RAYCHEL_BEGIN_TEST(test_name, test_tag)                                                                                  \
    TEMPLATE_TEST_CASE(test_name, test_tag, RAYCHEL_TUPLE_TEST_TYPES)                                                            \
    {                                                                                                                            \
        using namespace Raychel;

#define RAYCHEL_END_TEST }

struct OtherTupleTag
{};
//OtherTupleTag -> Raychel::TupleTag is implicitly allowed
//Raychel::TupleTag -> OtherTupleTag is not allowed

//clang-format doesn't like these macros
// clang-format off

RAYCHEL_BEGIN_TEST("Creating tuples", "[RaychelMath][Tuple]")

    {
        constexpr Tuple<TestType, 3> t{};
        REQUIRE(t[0] == 0);
        REQUIRE(t[1] == 0);
        REQUIRE(t[2] == 0);
    }

    {
        constexpr Tuple<TestType, 3> t{1};
        REQUIRE(t[0] == 1);
        REQUIRE(t[1] == 0);
        REQUIRE(t[2] == 0);
    }

    {
        constexpr Tuple<TestType, 3> t{1, 2};
        REQUIRE(t[0] == 1);
        REQUIRE(t[1] == 2);
        REQUIRE(t[2] == 0);
    }

    {
        constexpr Tuple<TestType, 3> t{12U, static_cast<TestType>(-5L), 9ULL};
        REQUIRE(t[0] == 12);
        REQUIRE(t[1] == static_cast<TestType>(-5L));
        REQUIRE(t[2] == 9);
    }

    {
        constexpr std::array<TestType, 3> values{9, 5, static_cast<TestType>(-12)};
        constexpr Tuple<TestType, 3> t{values};
        REQUIRE(t[0] == 9);
        REQUIRE(t[1] == 5);
        REQUIRE(t[2] == static_cast<TestType>(-12));
    }

    {
        constexpr Tuple<TestType, 3, OtherTupleTag> my_tuple{1, 2, 3};
        constexpr Tuple<TestType, 3> t{my_tuple};

        REQUIRE(t[0] == my_tuple[0]);
        REQUIRE(t[1] == my_tuple[1]);
        REQUIRE(t[2] == my_tuple[2]);

    }
RAYCHEL_END_TEST

TEST_CASE("Tuple structured bindings", "[RaychelMath][Tuple]")
{

    constexpr Raychel::Tuple t{12, 19.5, -7};
    const auto[x, y, z] = t;

    REQUIRE(x == 12);
    REQUIRE(y == 19.5);
    REQUIRE(z == -7);
}

TEST_CASE("Iterating tuples", "[RaychelMath][Tuple]")
{
    constexpr std::array values{12, 19, -7};
    constexpr Raychel::Tuple t{values};

    auto it = values.begin();
    for(const auto elem : t) {
        REQUIRE(elem == *(it++));
    }
}

RAYCHEL_BEGIN_TEST("Adding tuples", "[RaychelMath][Tuple]")
    {
        constexpr Tuple<TestType, 3> a{1, 2, 3};
        constexpr Tuple<TestType, 3> b{4, 5, 6};
        constexpr auto c = a + b;

        REQUIRE(c[0] == 5);
        REQUIRE(c[1] == 7);
        REQUIRE(c[2] == 9);
    }

    {
        constexpr Tuple<TestType, 3, OtherTupleTag> a{1, 2, 3};
        constexpr Tuple<TestType, 3> b{4, 5, 6};
        constexpr auto c = a + b;

        REQUIRE(c[0] == 5);
        REQUIRE(c[1] == 7);
        REQUIRE(c[2] == 9);
    }
RAYCHEL_END_TEST

RAYCHEL_BEGIN_TEST("Subtracting tuples", "[RaychelMath][Tuple]")
    {
        constexpr Tuple<TestType, 3> a{4, 5, 6};
        constexpr Tuple<TestType, 3> b{3, 2, 1};
        constexpr auto c = a - b;

        REQUIRE(c[0] == 1);
        REQUIRE(c[1] == 3);
        REQUIRE(c[2] == 5);
    }

    {
        constexpr Tuple<TestType, 3, OtherTupleTag> a{4, 5, 6};
        constexpr Tuple<TestType, 3> b{3, 2, 1};
        constexpr auto c = a - b;

        REQUIRE(c[0] == 1);
        REQUIRE(c[1] == 3);
        REQUIRE(c[2] == 5);
    }
RAYCHEL_END_TEST

RAYCHEL_BEGIN_TEST("Scaling tuples", "[RaychelMath][Tuple]")
    {
        constexpr Tuple<TestType, 3> a{4, 5, 6};
        constexpr auto s{12};
        constexpr auto c = a * s;

        REQUIRE(c[0] == 48);
        REQUIRE(c[1] == 60);
        REQUIRE(c[2] == 72);
    }
RAYCHEL_END_TEST

RAYCHEL_BEGIN_TEST("Dividing tuples", "[RaychelMath][Tuple]")
    {
        constexpr Tuple<TestType, 3> a{48, 60, 72};
        constexpr auto s{12};
        constexpr auto c = a / s;

        REQUIRE(c[0] == 4);
        REQUIRE(c[1] == 5);
        REQUIRE(c[2] == 6);
    }
RAYCHEL_END_TEST

// clang-format on