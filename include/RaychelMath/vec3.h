/**
*\file vec3.h
*\author weckyy702 (weckyy702@gmail.com)
*\brief Header for 3 dimensional vector quantities
*\date 2021-03-24
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
#ifndef RAYCHEL_VEC3_H
#define RAYCHEL_VEC3_H

#include "Tuple.h"
#include "math.h"

#include <cmath>

namespace Raychel {

    struct Vec3Tag
    {};
    template <>
    struct tuple_convertable<Vec3Tag, TupleTag> : std::true_type
    {};

    template <Arithmetic T>
    using vec3 = Tuple<T, 3, Vec3Tag>;

    template <Arithmetic T>
    constexpr T dot(const vec3<T>& a, const vec3<T>& b) noexcept
    {
        return (a[0] * b[0]) + (a[1] * b[1]) + (a[2] * b[2]);
    }

    template <Arithmetic T>
    T mag(const vec3<T>& v) noexcept
    {
        return static_cast<T>(std::sqrt(mag_sq(v)));
    }

    template <Arithmetic T>
    constexpr T mag_sq(const vec3<T>& v) noexcept
    {
        return sq(v[0]) + sq(v[1]) + sq(v[2]);
    }

    template <Arithmetic T>
    T dist(const vec3<T>& a, const vec3<T>& b) noexcept
    {
        return mag(a - b);
    }

    template <Arithmetic T>
    constexpr T dist_sq(const vec3<T>& a, const vec3<T>& b) noexcept
    {
        return mag_sq(a - b);
    }

    template <std::floating_point T>
    vec3<T> normalize(const vec3<T>& v) noexcept
    {
        RAYCHEL_ASSERT(v != vec3<T>{});
        return v / mag(v);
    }

    // clang-format off

    template <Arithmetic T>
    constexpr vec3<T> cross(const vec3<T>& a, const vec3<T>& b) noexcept
    {
        return vec3<T> {
            (a[1] * b[2]) - (a[2] * b[1]),
            (a[2] * b[0]) - (a[0] * b[2]),
            (a[0] * b[1]) - (a[1] * b[0])
        };
    }

    // clang-format on

    template <Arithmetic T>
    constexpr vec3<T> lerp(const vec3<T>& a, const vec3<T>& b, T x) noexcept
    {
        return (x * b) + ((1 - x) * a);
    }

} // namespace Raychel

#endif /*!RAYCHEL_VEC3_H*/
