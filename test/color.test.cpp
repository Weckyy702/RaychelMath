#include <cstdint>
#include <limits>
#include <type_traits>
#include "catch2/catch.hpp"

#include "RaychelMath/color.h"
#include "RaychelMath/equivalent.h"

//clang-format doesn't like these macros
// clang-format off

// these are common types for colors
#define RAYCHEL_TEST_TYPES unsigned char, size_t, float, double, long double

#define RAYCHEL_BEGIN_TEST(name, tag)                                          \
    TEMPLATE_TEST_CASE(name, tag, RAYCHEL_TEST_TYPES)                          \
    {                                                                          \
        using namespace Raychel;                                               \
        using color = basic_color<TestType>;

#define RAYCHEL_END_TEST }

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
RAYCHEL_BEGIN_TEST("Creating colors", "[RaychelMath][ColorRGB]")
    const color c{1, 0, 124};
    REQUIRE(c.r() == 1);
    REQUIRE(c.g() == 0);
    REQUIRE(c.b() == 124);

    const color c2{1, 2};
    REQUIRE(c2.r() == 1);
    REQUIRE(c2.g() == 2);
    REQUIRE(c2.b() == 0);

    const color c3{1};
    REQUIRE(c3.r() == 1);
    REQUIRE(c3.g() == 1);
    REQUIRE(c3.b() == 1);

    const color c4 = c3;
    REQUIRE(c4.r() == c3[0]);
    REQUIRE(c4.g() == c3[1]);
    REQUIRE(c4.b() == c3[2]);
RAYCHEL_END_TEST

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
RAYCHEL_BEGIN_TEST("Color addition", "[RaychelMath][ColorRGB]")
    const color c{1, 1, 1};

    const color c2 = c + color{0, 1, 5};

    REQUIRE(c2.r() == 1);
    REQUIRE(c2.g() == 2);
    REQUIRE(c2.b() == 6);

    color c3{1, 1, 1};
    c3 += color{0, 1, 5};

    REQUIRE(c3.r() == 1);
    REQUIRE(c3.g() == 2);
    REQUIRE(c3.b() == 6);
RAYCHEL_END_TEST

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
RAYCHEL_BEGIN_TEST("Color subtraction", "[RaychelMath][ColorRGB]")
    const color c{128, 128, 128};

    const auto res = c - color{64, 128, 5};

    REQUIRE(res.r() == 64);
    REQUIRE(res.g() == 0);
    REQUIRE(res.b() == 123);

    color c2{128, 128, 128};
    c2 -= color{64, 128, 5};

    REQUIRE(c2.r() == 64);
    REQUIRE(c2.g() == 0);
    REQUIRE(c2.b() == 123);
RAYCHEL_END_TEST

//FIXME: implement color inversion
// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
//TEST_CASE("Inverting colors", "[RaychelMath][ColorRGB]")
//{
//    {
//        constexpr Raychel::color<float> c{0.0F, 0.35F, 1.0F};
//
//        constexpr auto res = -c;
//
//        REQUIRE(res.r() == 1.0F);
//        REQUIRE(res.g() == 0.65F);
//        REQUIRE(res.b() == 0.0F);
//    }
//
//    {
//        const Raychel::color<unsigned char> c{0, 91, 255};
//
//        const auto res = -c;
//
//        REQUIRE(res.r() == 255);
//        REQUIRE(res.g() == 164);
//        REQUIRE(res.b() == 0);
//    }
//}

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
RAYCHEL_BEGIN_TEST("Color multiplication", "[RaychelMath][ColorRGB]")
    const color c{12, 12, 12};

    color res = c * color{5, 0, 2};
    REQUIRE(res.r() == 60);
    REQUIRE(res.g() == 0);
    REQUIRE(res.b() == 24);

    res = c * TestType{2};
    REQUIRE(res.r() == 24);
    REQUIRE(res.g() == 24);
    REQUIRE(res.b() == 24);

    if constexpr (std::is_floating_point_v<TestType>) {
        const color c1{1, 0, .5};

        res = c1 * color{0.5, 0.25, 2.5};

        REQUIRE(res.r() == 0.5);
        REQUIRE(res.g() == 0);
        REQUIRE(res.b() == 1.25);


        res = c1 * TestType{0.5};

        REQUIRE(res.r() == 0.5);
        REQUIRE(res.g() == 0);
        REQUIRE(res.b() == .25);
    }

RAYCHEL_END_TEST

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
RAYCHEL_BEGIN_TEST("Color Division", "[RaychelMath][ColorRGB]")

    color c{12, 246, 18};

    c /= 2;

    REQUIRE(c.r() == 6);
    REQUIRE(c.g() == 123);
    REQUIRE(c.b() == 9);

RAYCHEL_END_TEST

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
RAYCHEL_BEGIN_TEST("Color comparison: equality", "[RaychelMath][ColorRGB]")

    const color c{1, 12, 5};

    REQUIRE(c == c);
    REQUIRE(c == color{1, 12, 5});

    REQUIRE(c != color{0, 5, 42});

RAYCHEL_END_TEST

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
RAYCHEL_BEGIN_TEST("Color brightness", "[RaychelMath][ColorRGB]")

    const color c{3, 4, 5};
    const auto b = brightness(c);

    REQUIRE(b == 4);

RAYCHEL_END_TEST

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
TEST_CASE("Color conversion", "[RaychelMath][ColorRGB]")
{
    using namespace Raychel;

    constexpr basic_color<int> c{536870911, 2147483647, 0}; //RGB-8: 63, 255, 0

    constexpr auto c_u8 = convert_color<unsigned char>(c); //integral(large) -> integral(small)

    REQUIRE(c_u8.r() == 63);
    REQUIRE(c_u8.g() == 255);
    REQUIRE(c_u8.b() == 0);

    auto c_64 = convert_color<std::int64_t>(c_u8); //integral(small) -> integral(large)

    REQUIRE(c_64.r() == 2278715444399415168L);
    REQUIRE(c_64.g() == 9223372036854775680L);
    REQUIRE(c_64.b() == 0L);

    constexpr auto c_float = convert_color<float>(c_u8); //integral(small) -> floating point

    REQUIRE(c_float.r() == 63/255.0F);
    REQUIRE(c_float.g() == 1.0F);
    REQUIRE(c_float.b() == 0.0F);

    constexpr auto c_double = convert_color<double>(c_float); //floating point -> floating point
    REQUIRE(c_double.r() == Approx(63/255.0));
    REQUIRE(c_double.g() == 1.0);
    REQUIRE(c_double.b() == 0.0);

    constexpr auto c_u16 = convert_color<std::uint16_t>(c_double); //floating point -> integral;
    REQUIRE(c_u16.r() == 16191U);
    REQUIRE(c_u16.g() == 65535U);
    REQUIRE(c_u16.b() == 0U);
}

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
RAYCHEL_BEGIN_TEST("Color from RGB", "[RaychelMath][ColorRGB]")

    constexpr TestType max = std::is_integral_v<TestType> ? std::numeric_limits<TestType>::max() : TestType{1};
    constexpr TestType half = (128.0L / 255.0L) * max;

    constexpr auto black = color_from_rgb<TestType>(0, 0, 0);
    constexpr auto white = color_from_rgb<TestType>(255, 255, 255);
    constexpr auto red = color_from_rgb<TestType>(255, 0, 0);
    constexpr auto green = color_from_rgb<TestType>(0, 255, 0);
    constexpr auto blue = color_from_rgb<TestType>(0, 0, 255);
    constexpr auto dark_yellow = color_from_rgb<TestType>(128, 128, 0);


    REQUIRE(black.r() == 0);
    REQUIRE(black.g() == 0);
    REQUIRE(black.b() == 0);

    REQUIRE(white.r() == max);
    REQUIRE(white.g() == max);
    REQUIRE(white.b() == max);

    REQUIRE(red.r() == max);
    REQUIRE(red.g() == 0);
    REQUIRE(red.b() == 0);

    REQUIRE(green.r() == 0);
    REQUIRE(green.g() == max);
    REQUIRE(green.b() == 0);

    REQUIRE(blue.r() == 0);
    REQUIRE(blue.g() == 0);
    REQUIRE(blue.b() == max);

    REQUIRE(dark_yellow.r() == half);
    REQUIRE(dark_yellow.g() == half);
    REQUIRE(dark_yellow.b() == 0);

RAYCHEL_END_TEST

//NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
RAYCHEL_BEGIN_TEST("Color from HEX", "[RaychelMath][ColorRGB]")

    constexpr TestType max = std::is_integral_v<TestType> ? std::numeric_limits<TestType>::max() : TestType{1};
    constexpr TestType half = (128.0L / 255.0L) * max;

    constexpr auto black = color_from_hex<TestType>(0x000000);
    constexpr auto white = color_from_hex<TestType>(0xFFFFFF);
    constexpr auto red = color_from_hex<TestType>(0xFF0000);
    constexpr auto green = color_from_hex<TestType>(0x00FF00);
    constexpr auto blue = color_from_hex<TestType>(0x0000FF);
    constexpr auto dark_yellow = color_from_hex<TestType>(0x808000);


    REQUIRE(black.r() == 0);
    REQUIRE(black.g() == 0);
    REQUIRE(black.b() == 0);

    REQUIRE(white.r() == max);
    REQUIRE(white.g() == max);
    REQUIRE(white.b() == max);

    REQUIRE(red.r() == max);
    REQUIRE(red.g() == 0);
    REQUIRE(red.b() == 0);

    REQUIRE(green.r() == 0);
    REQUIRE(green.g() == max);
    REQUIRE(green.b() == 0);

    REQUIRE(blue.r() == 0);
    REQUIRE(blue.g() == 0);
    REQUIRE(blue.b() == max);

    REQUIRE(equivalent<TestType>(dark_yellow.r(), half));
    REQUIRE(equivalent<TestType>(dark_yellow.g(), half));
    REQUIRE(dark_yellow.b() == 0);

RAYCHEL_END_TEST

//NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
RAYCHEL_BEGIN_TEST("Color from temperature", "[RaychelMath][ColorRGB]")
    //Test cases taken from https://github.com/m-lima/tempergb

    using c = basic_color<std::uint8_t>;

    const auto expect_color = [](std::uint32_t temp, c _expected){
        const auto given = color_from_temperature<TestType>(temp);
        const auto expected = convert_color<TestType>(_expected);

        REQUIRE(given == expected);
    };

    expect_color(0, c{255, 67, 0});
    expect_color(1500, c{255, 108, 0});
    expect_color(2500, c{255, 159, 70});
    expect_color(5000, c{255, 228, 205});
    expect_color(6600, c{255, 255, 255});
    expect_color(10'000, c{201, 218, 255});
    expect_color(15'000, c{181, 205, 255});
    expect_color(40'000, c{151, 185, 255});
    expect_color(60'000, c{151, 185, 255});

RAYCHEL_END_TEST
