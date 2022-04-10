/**
*\file Quaternion.h
*\author weckyy702 (weckyy702@gmail.com)
*\brief Header file for Quatenions
*\date 2021-03-23
*
*MIT License
*Copyright (c) [2021] [Weckyy702 (weckyy702@gmail.com | https://github.com/Weckyy702)]
*Permission is hereby granted, free of charge, to any person obtaining a copy
*of this software and associated documentation files (the "Software"), to deal
*in the Software without restriction, including without limitation the rights
*to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*copies of the Software, and to permit persons to whom the Software is
*furnished to do so, subject to the following conditions:
*
*The above copyright notice and this permission notice shall be included in all
*copies or substantial portions of the Software.
*
*THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
*SOFTWARE.
*
*/
#ifndef RAYCHEL_QUATERNION_H
#define RAYCHEL_QUATERNION_H

#include <type_traits>
#include "Tuple.h"
#include "vec3.h"
#include "constants.h"

namespace Raychel {
    struct QuaternionTag
    {};

    template <>
    struct tuple_convertable<QuaternionTag, Vec3Tag> : std::true_type
    {};

    template <Arithmetic T>
    using basic_quaternion = Tuple<T, 4, QuaternionTag>;

    template <Arithmetic T, std::convertible_to<T> T_>
    constexpr basic_quaternion<T> rotate_around(const basic_vec3<T>& _axis, T_ angle_in_rads)
    {
        RAYCHEL_ASSERT(_axis != basic_vec3<T>{});
        const auto half_angle = angle_in_rads / 2;

        const auto s = std::sin(half_angle);
        const auto axis = normalize(_axis);

        const auto r = std::cos(half_angle);
        const auto i = axis[0] * s;
        const auto j = axis[1] * s;
        const auto k = axis[2] * s;

        return basic_quaternion<T>{r, i, j, k};
    }

    template <Arithmetic T>
    constexpr basic_vec3<T> v(const basic_quaternion<T>& q)
    {
        return {q[1], q[2], q[3]};
    }

    template <Arithmetic T>
    constexpr basic_quaternion<T>& operator*=(basic_quaternion<T>& a, const basic_quaternion<T>& b)
    {
        const auto r = a[0];
        const auto i = a[1];
        const auto j = a[2];
        const auto k = a[3];

        a[0] = r * b[0] - i * b[1] - j * b[2] - k * b[3];
        a[1] = r * b[1] + i * b[0] + j * b[3] - k * b[2];
        a[2] = r * b[2] - i * b[3] + j * b[0] + k * b[1];
        a[3] = r * b[3] + i * b[2] - j * b[1] + k * b[0];

        return a;
    }

    template <Arithmetic T>
    constexpr basic_quaternion<T>& operator/=(basic_quaternion<T>& a, const basic_quaternion<T>& b)
    {
        return a *= inverse(b);
    }

    template <Arithmetic T>
    constexpr auto operator*(const basic_quaternion<T>& a, const basic_quaternion<T>& b)
    {
        auto q{a};
        q *= b;
        return q;
    }

    template <Arithmetic T>
    constexpr auto operator*(const basic_vec3<T>& v, const basic_quaternion<T>& _q)
    {
        RAYCHEL_ASSERT(_q != basic_quaternion<T>{});
        const auto q = normalize(_q);

        //following is the expanded and somewhat optimized version of q * p * q^-1 with p = basic_quaternionImp{0.0, v[0], v.y, v.z}
        const auto r = q[1] * v[0] + q[2] * v[1] + q[3] * v[2];
        const auto i = q[0] * v[0] + q[2] * v[2] - q[3] * v[1];
        const auto j = q[0] * v[1] - q[1] * v[2] + q[3] * v[0];
        const auto k = q[0] * v[2] + q[1] * v[1] - q[2] * v[0];

        const auto x = r * q[1] + i * q[0] - j * q[3] + k * q[2];
        const auto y = r * q[2] + i * q[3] + j * q[0] - k * q[1];
        const auto z = r * q[3] - i * q[2] + j * q[1] + k * q[0];

        return basic_vec3<T>{x, y, z};
    }

    template <Arithmetic T>
    constexpr auto operator/(const basic_quaternion<T>& a, const basic_quaternion<T>& b)
    {
        return a * inverse(b);
    }

    template <Arithmetic T>
    constexpr T dot(const basic_quaternion<T>& a, const basic_quaternion<T>& b)
    {
        return a[0] * b[0] + a[1] * b[1] + a[2] * b[2] + a[3] * b[3];
    }

    template <Arithmetic T>
    constexpr T mag_sq(const basic_quaternion<T>& q)
    {
        return sq(q[0]) + sq(q[1]) + sq(q[2]) + sq(q[3]);
    }

    template <Arithmetic T>
    constexpr T mag(const basic_quaternion<T>& q)
    {
        return std::sqrt(mag_sq(q));
    }

    template <Arithmetic T>
    constexpr auto normalize(const basic_quaternion<T>& q)
    {
        return q / mag(q);
    }

    template <Arithmetic T>
    constexpr auto conjugate(const basic_quaternion<T>& q)
    {
        return basic_quaternion<T>{q[0], -q[1], -q[2], -q[3]};
    }

    template <Arithmetic T>
    constexpr auto inverse(const basic_quaternion<T>& q)
    {
        return conjugate(q) / mag_sq(q);
    }

    template <std::floating_point T, std::convertible_to<T> T_>
    constexpr basic_quaternion<T> lerp(const basic_quaternion<T>& _a, const basic_quaternion<T>& _b, T_ x)
    {
        constexpr T threshold{0.995}; //TODO: make this adjustable

        const auto a = normalize(_a);
        const auto b = normalize(_b);

        auto d = dot(v(a), v(b));

        if (d < 0) {
            a *= -1;
            b *= -1;
        }

        if (d >= threshold) {
            return normalize(a * x + b * (1 - x));
        }

        const auto theta0 = std::acos(d);
        const auto theta = theta0 * x;
        const auto sin_theta = std::sin(theta);
        const auto sin_theta0 = std::sin(theta0);

        const auto s1 = sin_theta / sin_theta0;
        const auto s0 = std::cos(theta) - (d * s1);

        return (a * s0) + (b * s1);
    }

    template<Arithmetic T>
    constexpr basic_quaternion<T> look_at(const basic_vec3<T>& old_forward, const basic_vec3<T>& new_forward)
    {
        constexpr T threshold = 0.9998;

        const auto k_cos_theta = dot(old_forward, new_forward);
        const auto k = std::sqrt(mag_sq(old_forward) * mag_sq(new_forward));

        if((k_cos_theta) / k < -threshold){
            const auto orth = get_tangent(old_forward);
            return rotate_around(orth, pi<T>);
        }
    }

} // namespace Raychel

#endif /*!RAYCHEL_QUATERNION_H*/
