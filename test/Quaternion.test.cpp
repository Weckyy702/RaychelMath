#include "catch2/catch.hpp"

#define RAYCHEL_LOGICALLY_EQUAL 1

#include "RaychelMath/Quaternion.h"
#include "RaychelMath/equivalent.h"

//clang-format doesn't like these macros
// clang-format off

#define RAYCHEL_QUATERNION_TEST_TYPES float, double, long double
#define RAYCHEL_BEGIN_TEST(test_name, test_tag)                                                                                  \
    TEMPLATE_TEST_CASE(test_name, test_tag, RAYCHEL_QUATERNION_TEST_TYPES)                                                       \
    {                                                                                                                            \
        using namespace Raychel;                                                                                                 \
        using Quaternion = basic_quaternion<TestType>;                                                                              \
        using vec3 = basic_vec3<TestType>;

#define RAYCHEL_END_TEST }


RAYCHEL_BEGIN_TEST("Creating Quaternions", "[RaychelMath][Quaternion]")

    const TestType one_over_sqrt2 = 1.0L / std::sqrt(2.0L);
    const TestType sin_eighth_pi = std::sin(quarter_pi<long double> * 0.5L);
    const TestType cos_eighth_pi = std::cos(quarter_pi<long double> * 0.5L);

    const Quaternion a{};
    const Quaternion b{12, 7, 19, 4};
    const auto c = rotate_around(vec3{0, 1, 0}, 0);
    const auto d = rotate_around(vec3{1, 0, 1}, half_pi<TestType>);
    const auto e = rotate_around(vec3{-9, 12, 20}, quarter_pi<TestType>);

    REQUIRE(a[0] == 0);
    REQUIRE(a[1] == 0);
    REQUIRE(a[2] == 0);
    REQUIRE(a[3] == 0);

    REQUIRE(b[0] == 12);
    REQUIRE(b[1] == 7);
    REQUIRE(b[2] == 19);
    REQUIRE(b[3] == 4);

    REQUIRE(c[0] == 1);
    REQUIRE(c[1] == 0);
    REQUIRE(c[2] == 0);
    REQUIRE(c[3] == 0);

    REQUIRE(equivalent<TestType>(d[0], one_over_sqrt2));
    REQUIRE(equivalent<TestType>(d[1], 0.5));
    REQUIRE(d[2] == 0);
    REQUIRE(equivalent<TestType>(d[3], 0.5));

    REQUIRE(equivalent<TestType>(e[0], cos_eighth_pi));
    REQUIRE(equivalent<TestType>(e[1], -.36 * sin_eighth_pi));
    REQUIRE(equivalent<TestType>(e[2], .48 * sin_eighth_pi));
    REQUIRE(equivalent<TestType>(e[3], .8 * sin_eighth_pi));

RAYCHEL_END_TEST


RAYCHEL_BEGIN_TEST("Quaternion addition", "[RaychelMath][Quaternion]")

    Quaternion q{12, 7, 9, 14};

    const auto res = q + Quaternion{-5, 19, 3, -35};

    REQUIRE(res[0] == 7);
    REQUIRE(res[1] == 26);
    REQUIRE(res[2] == 12);
    REQUIRE(res[3] == -21);

    q += Quaternion{7, 4, -12, 9};

    REQUIRE(q[0] == 19);
    REQUIRE(q[1] == 11);
    REQUIRE(q[2] == -3);
    REQUIRE(q[3] == 23);

RAYCHEL_END_TEST


RAYCHEL_BEGIN_TEST("Quaternion subtraction", "[RaychelMath][Quaternion]")

    Quaternion q{12, 7, 9, 14};

    const auto res = q - Quaternion{-5, 19, 3, -35};

    REQUIRE(res[0] == 17);
    REQUIRE(res[1] == -12);
    REQUIRE(res[2] == 6);
    REQUIRE(res[3] == 49);

    q -= Quaternion{7, 4, -12, 9};

    REQUIRE(q[0] == 5);
    REQUIRE(q[1] == 3);
    REQUIRE(q[2] == 21);
    REQUIRE(q[3] == 5);

    const auto q2 = -q;

    REQUIRE(q2[0] == -5);
    REQUIRE(q2[1] == -3);
    REQUIRE(q2[2] == -21);
    REQUIRE(q2[3] == -5);

RAYCHEL_END_TEST


RAYCHEL_BEGIN_TEST("Quaternion multiplication: Quaternion", "[RaychelMath][Quaternion]")

    Quaternion a{12, 7, 9, 4};
    Quaternion b{-1, 0.5, 7, 113};

    const auto ab = a * b;

    REQUIRE(ab[0] == -530.5);
    REQUIRE(ab[1] == 988);
    REQUIRE(ab[2] == -714);
    REQUIRE(ab[3] == 1396.5);

    //Quaternion multiplication is non-commutative, so a * b != b * a
    const auto ba = b * a;

    REQUIRE(ba[0] == -530.5);
    REQUIRE(ba[1] == -990);
    REQUIRE(ba[2] == 864);
    REQUIRE(ba[3] == 1307.5);

    auto _a = a;
    auto _b = b;

    _a *= b;

    REQUIRE(_a[0] == -530.5);
    REQUIRE(_a[1] == 988);
    REQUIRE(_a[2] == -714);
    REQUIRE(_a[3] == 1396.5);

    _b *= a;

    REQUIRE(_b[0] == -530.5);
    REQUIRE(_b[1] == -990);
    REQUIRE(_b[2] == 864);
    REQUIRE(_b[3] == 1307.5);

RAYCHEL_END_TEST


RAYCHEL_BEGIN_TEST("Quaternion multiplication: Scalar", "[RaychelMath][Quaternion]")

    const TestType s = -0.5;
    Quaternion a{12, 7.5, -3, 9};

    const auto res = a * s;

    REQUIRE(res[0] == -6);
    REQUIRE(res[1] == -3.75);
    REQUIRE(res[2] == 1.5);
    REQUIRE(res[3] == -4.5);

    a *= s;

    REQUIRE(a[0] == -6);
    REQUIRE(a[1] == -3.75);
    REQUIRE(a[2] == 1.5);
    REQUIRE(a[3] == -4.5);

RAYCHEL_END_TEST


RAYCHEL_BEGIN_TEST("Quaternion multiplication: Vector", "[RaychelMath][Quaternion]")

    const vec3 x{1, 0, 0};
    const vec3 y{0, 1, 0};
    const vec3 z{0, 0, 1};
    const vec3 v{12.345, -7.99, 4};

    const auto a = rotate_around(vec3{2, 0, -1}, pi_v<TestType>);

    const auto x_r = x * a;

    REQUIRE(equivalent<TestType>(x_r[0], 0.6));
    REQUIRE(equivalent<TestType>(x_r[1], 0));
    REQUIRE(equivalent<TestType>(x_r[2], -0.8));

    const auto y_r = y * a;

    REQUIRE(equivalent<TestType>(y_r[0], 0));
    REQUIRE(equivalent<TestType>(y_r[1], -1));
    REQUIRE(equivalent<TestType>(y_r[2], 0));

    const auto z_r = z * a;

    REQUIRE(equivalent<TestType>(z_r[0], -0.8));
    REQUIRE(equivalent<TestType>(z_r[1], 0));
    REQUIRE(equivalent<TestType>(z_r[2], -0.6));

    const auto v_r = v * a;

    REQUIRE(equivalent<TestType>(v_r[0], 4.207));
    REQUIRE(equivalent<TestType>(v_r[1], 7.99));
    REQUIRE(equivalent<TestType>(v_r[2], -12.276));

RAYCHEL_END_TEST


RAYCHEL_BEGIN_TEST("Quaternion division: Quaternion", "[RaychelMath][Quaternion]")

    Quaternion q{12, -4.5, -6, 9};
    const Quaternion b{1, 2, 3, 4};

    auto res = q / b;

    REQUIRE(equivalent<TestType>(res[0], 0.7));
    REQUIRE(equivalent<TestType>(res[1], 0.75));
    REQUIRE(equivalent<TestType>(res[2], -2.6));
    REQUIRE(equivalent<TestType>(res[3], -1.25));

    res = b / q;

    REQUIRE(equivalent<TestType>(res[0], 89.6/1200.0L));
    REQUIRE(equivalent<TestType>(res[1], -0.08));
    REQUIRE(equivalent<TestType>(res[2], 8.32/30.0L));
    REQUIRE(equivalent<TestType>(res[3], 4/30.0L));

    q /= b;

    REQUIRE(equivalent<TestType>(q[0], 0.7));
    REQUIRE(equivalent<TestType>(q[1], 0.75));
    REQUIRE(equivalent<TestType>(q[2], -2.6));
    REQUIRE(equivalent<TestType>(q[3], -1.25));

    res = b / b;

    REQUIRE(equivalent<TestType>(res[0], 1));
    REQUIRE(equivalent<TestType>(res[1], 0));
    REQUIRE(equivalent<TestType>(res[2], 0));
    REQUIRE(equivalent<TestType>(res[3], 0));

RAYCHEL_END_TEST


RAYCHEL_BEGIN_TEST("Quaternion division: scalar", "[RaychelMath][Quaternion]")

    Quaternion q{12, -4.5, -6, 9};
    const TestType s = 2;

    const auto res = q / s;

    REQUIRE(res[0] == 6);
    REQUIRE(res[1] == -2.25);
    REQUIRE(res[2] == -3);
    REQUIRE(res[3] == 4.5);

    q /= s;

    REQUIRE(q[0] == 6);
    REQUIRE(q[1] == -2.25);
    REQUIRE(q[2] == -3);
    REQUIRE(q[3] == 4.5);

RAYCHEL_END_TEST


RAYCHEL_BEGIN_TEST("Quaternion dot product", "[RaychelMath][Quaternion]")

    Quaternion a{12, 9, 17, 4};
    Quaternion b = a;

    auto res = dot(a, b);

    REQUIRE(res == 530);
    REQUIRE(res == dot(b, a));

    b = -a;
    res = dot(a, b);

    REQUIRE(res == -530);
    REQUIRE(res == dot(b, a));

    a = Quaternion{0, 1, 0, 1};
    b = Quaternion{1, 0, 1, 0};

    REQUIRE(dot(a, b) == 0);
    REQUIRE(dot(b, a) == 0);

RAYCHEL_END_TEST


RAYCHEL_BEGIN_TEST("Quaternion magnitude", "[RaychelMath][Quaternion]")

    const auto sqrt_299 = std::sqrt(TestType{299});
    Quaternion q{12, 7, -9, 5};

    const auto res = mag(q);

    REQUIRE(res == sqrt_299);

    q = Quaternion{};

    REQUIRE(mag(q) == 0);

    q = Quaternion{0, 0, 0, 0};

    REQUIRE(mag(q) == 0);

RAYCHEL_END_TEST


RAYCHEL_BEGIN_TEST("Quaternion magnitude squared", "[RaychelMath][Quaternion]")

    Quaternion q{12, 7, -9, 5};

    const auto res = mag_sq(q);

    REQUIRE(res == 299);

    q = Quaternion{};

    REQUIRE(mag_sq(q) == 0);

RAYCHEL_END_TEST


RAYCHEL_BEGIN_TEST("Quaternion normalization", "[RaychelMath][Quaternion]")

    Quaternion q{1, 5, -7, 4};

    auto res = normalize(q);

    REQUIRE(equivalent<TestType>(mag(res), 1.0));

RAYCHEL_END_TEST


RAYCHEL_BEGIN_TEST("Quaternion conjugate", "[RaychelMath][Quaternion]")

    const Quaternion q{1, 0, -5, 9};
    const auto res = conjugate(q);

    REQUIRE(res[0] == 1);
    REQUIRE(res[1] == 0);
    REQUIRE(res[2] == 5);
    REQUIRE(res[3] == -9);

RAYCHEL_END_TEST

//NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
RAYCHEL_BEGIN_TEST("Quaternion inverse", "[RaychelMath][Quaternion]")

    const Quaternion q{12, -5, 17, 9};

    const TestType q_mag_sq = sq(q[0]) + sq(q[1]) + sq(q[2]) + sq(q[3]);
    const auto r =  q[0] / q_mag_sq;
    const auto i = -q[1] / q_mag_sq;
    const auto j = -q[2] / q_mag_sq;
    const auto k = -q[3] / q_mag_sq;

    const auto res = inverse(q);

    REQUIRE(equivalent<TestType>(res[0], r));
    REQUIRE(equivalent<TestType>(res[1], i));
    REQUIRE(equivalent<TestType>(res[2], j));
    REQUIRE(equivalent<TestType>(res[3], k));

RAYCHEL_END_TEST

//TODO: fix this
//NOLINTNEXTLINE: i am using a *macro*! :O (despicable)
// RAYCHEL_BEGIN_TEST("Quaternion look_at", "[RaychelMath][Quaternion]")
//     const TestType one_over_sqrt2 = 1 / std::sqrt(2.0);
//     const vec3 forward{0, 0, 1};

//     vec3 origin{};
//     vec3 target{0, 0, 12};
//     vec3 target_dir = normalize(target-origin);

//     auto dir = look_at(forward, target_dir);

//     REQUIRE(dir[0] == 1);
//     REQUIRE(dir[1] == 0);
//     REQUIRE(dir[2] == 0);
//     REQUIRE(dir[3] == 0);


//     target = vec3{1, 0, 0};
//     dir = look_at(forward, target_dir);

//     REQUIRE(equivalent<TestType>(dir[0], one_over_sqrt2));
//     REQUIRE(dir[1] == 0);
//     REQUIRE(equivalent<TestType>(dir[2], one_over_sqrt2));
//     REQUIRE(dir[3] == 0);


//     origin = vec3{1, 1, 1};
//     target = vec3{};

//     dir = look_at(forward, target_dir);

//     REQUIRE((forward * dir) == normalize(target_dir));

//     origin = normalize(vec3{12, 7, 19}) * (TestType)7;
//     dir = look_at(forward, target_dir);

//     REQUIRE((forward * dir) == normalize(target_dir));


// RAYCHEL_END_TEST
