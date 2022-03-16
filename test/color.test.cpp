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
        using color = color<TestType>;

#define RAYCHEL_END_TEST }

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
RAYCHEL_BEGIN_TEST("Creating colors", "[RaychelMath][ColorRGB]")
    const color c{1, 0, 124};
    REQUIRE(c[0] == 1);
    REQUIRE(c[1] == 0);
    REQUIRE(c[2] == 124);

    const color c2{1, 2};
    REQUIRE(c2[0] == 1);
    REQUIRE(c2[1] == 2);
    REQUIRE(c2[2] == 0);

    //FIXME: our new implementation changes the behaviour from c={1, 1, 1} to c={1, 0, 0}!!
    const color c3{1};
    REQUIRE(c3[0] == 1);
    REQUIRE(c3[1] == 0);
    REQUIRE(c3[2] == 0);

    const color c4 = c3;
    REQUIRE(c4[0] == c3[0]);
    REQUIRE(c4[1] == c3[1]);
    REQUIRE(c4[2] == c3[2]);
RAYCHEL_END_TEST

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
RAYCHEL_BEGIN_TEST("Color addition", "[RaychelMath][ColorRGB]")
    const color c{1, 1, 1};

    const color c2 = c + color{0, 1, 5};

    REQUIRE(c2[0] == 1);
    REQUIRE(c2[1] == 2);
    REQUIRE(c2[2] == 6);

    color c3{1, 1, 1};
    c3 += color{0, 1, 5};

    REQUIRE(c3[0] == 1);
    REQUIRE(c3[1] == 2);
    REQUIRE(c3[2] == 6);
RAYCHEL_END_TEST

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
RAYCHEL_BEGIN_TEST("Color subtraction", "[RaychelMath][ColorRGB]")
    const color c{128, 128, 128};

    const auto res = c - color{64, 128, 5};

    REQUIRE(res[0] == 64);
    REQUIRE(res[1] == 0);
    REQUIRE(res[2] == 123);

    color c2{128, 128, 128};
    c2 -= color{64, 128, 5};

    REQUIRE(c2[0] == 64);
    REQUIRE(c2[1] == 0);
    REQUIRE(c2[2] == 123);
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
//        REQUIRE(res[0] == 1.0F);
//        REQUIRE(res[1] == 0.65F);
//        REQUIRE(res[2] == 0.0F);
//    }
//
//    {
//        const Raychel::color<unsigned char> c{0, 91, 255};
//
//        const auto res = -c;
//
//        REQUIRE(res[0] == 255);
//        REQUIRE(res[1] == 164);
//        REQUIRE(res[2] == 0);
//    }
//}

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
RAYCHEL_BEGIN_TEST("Color multiplication", "[RaychelMath][ColorRGB]")
    const color c{12, 12, 12};

    color res = c * color{5, 0, 2};
    REQUIRE(res[0] == 60);
    REQUIRE(res[1] == 0);
    REQUIRE(res[2] == 24);

    res = c * TestType{2};
    REQUIRE(res[0] == 24);
    REQUIRE(res[1] == 24);
    REQUIRE(res[2] == 24);

    if constexpr (std::is_floating_point_v<TestType>) {
        const color c1{1, 0, .5};

        res = c1 * color{0.5, 0.25, 2.5};

        REQUIRE(res[0] == 0.5);
        REQUIRE(res[1] == 0);
        REQUIRE(res[2] == 1.25);


        res = c1 * TestType{0.5};

        REQUIRE(res[0] == 0.5);
        REQUIRE(res[1] == 0);
        REQUIRE(res[2] == .25);
    }

RAYCHEL_END_TEST

// NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
RAYCHEL_BEGIN_TEST("Color Division", "[RaychelMath][ColorRGB]")

    color c{12, 246, 18};

    c /= 2;

    REQUIRE(c[0] == 6);
    REQUIRE(c[1] == 123);
    REQUIRE(c[2] == 9);

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

    constexpr color<int> c{536870911, 2147483647, 0}; //RGB-8: 63, 255, 0

    constexpr auto c_u8 = convert_color<unsigned char>(c); //integral(large) -> integral(small)

    REQUIRE(c_u8[0] == 63);
    REQUIRE(c_u8[1] == 255);
    REQUIRE(c_u8[2] == 0);

    auto c_64 = convert_color<std::int64_t>(c_u8); //integral(small) -> integral(large)

    REQUIRE(c_64[0] == 2278715444399415168L);
    REQUIRE(c_64[1] == 9223372036854775680L);
    REQUIRE(c_64[2] == 0L);

    constexpr auto c_float = convert_color<float>(c_u8); //integral(small) -> floating point

    REQUIRE(c_float[0] == 63/255.0F);
    REQUIRE(c_float[1] == 1.0F);
    REQUIRE(c_float[2] == 0.0F);

    constexpr auto c_double = convert_color<double>(c_float); //floating point -> floating point
    REQUIRE(c_double[0] == Approx(63/255.0));
    REQUIRE(c_double[1] == 1.0);
    REQUIRE(c_double[2] == 0.0);

    constexpr auto c_u16 = convert_color<std::uint16_t>(c_double); //floating point -> integral;
    REQUIRE(c_u16[0] == 16191U);
    REQUIRE(c_u16[1] == 65535U);
    REQUIRE(c_u16[2] == 0U);
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


    REQUIRE(black[0] == 0);
    REQUIRE(black[1] == 0);
    REQUIRE(black[2] == 0);

    REQUIRE(white[0] == max);
    REQUIRE(white[1] == max);
    REQUIRE(white[2] == max);

    REQUIRE(red[0] == max);
    REQUIRE(red[1] == 0);
    REQUIRE(red[2] == 0);

    REQUIRE(green[0] == 0);
    REQUIRE(green[1] == max);
    REQUIRE(green[2] == 0);

    REQUIRE(blue[0] == 0);
    REQUIRE(blue[1] == 0);
    REQUIRE(blue[2] == max);

    REQUIRE(dark_yellow[0] == half);
    REQUIRE(dark_yellow[1] == half);
    REQUIRE(dark_yellow[2] == 0);

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


    REQUIRE(black[0] == 0);
    REQUIRE(black[1] == 0);
    REQUIRE(black[2] == 0);

    REQUIRE(white[0] == max);
    REQUIRE(white[1] == max);
    REQUIRE(white[2] == max);

    REQUIRE(red[0] == max);
    REQUIRE(red[1] == 0);
    REQUIRE(red[2] == 0);

    REQUIRE(green[0] == 0);
    REQUIRE(green[1] == max);
    REQUIRE(green[2] == 0);

    REQUIRE(blue[0] == 0);
    REQUIRE(blue[1] == 0);
    REQUIRE(blue[2] == max);

    REQUIRE(equivalent<TestType>(dark_yellow[0], half));
    REQUIRE(equivalent<TestType>(dark_yellow[1], half));
    REQUIRE(dark_yellow[2] == 0);

RAYCHEL_END_TEST