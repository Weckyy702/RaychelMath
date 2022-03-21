/**
*\file vec2.h
*\author weckyy702 (weckyy702@gmail.com)
*\brief Header file for 2 dimensional vector quantities
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
#ifndef RAYCHEL_VEC2_H
#define RAYCHEL_VEC2_H

#include "Tuple.h"
#include "forward.h"
#include "math.h"
namespace Raychel {

    struct vec2Tag
    {};

    template <Arithmetic T>
    using vec2 = Tuple<T, 2, vec2Tag>;

    template <>
    struct tuple_convertable<vec2Tag, vec3Tag> : std::true_type
    {};

    template <Arithmetic T>
    constexpr T dot(const vec2<T>& a, const vec2<T>& b)
    {
        return a[0] * b[0] + a[1] * b[1];
    }

    template <Arithmetic T>
    T mag(const vec2<T>& v)
    {
        return std::sqrt(mag_sq(v));
    }

    template <Arithmetic T>
    constexpr T mag_sq(const vec2<T>& v)
    {
        return sq(v[0]) + sq(v[1]);
    }

    template <std::floating_point T>
    vec2<T> normalize(const vec2<T>& v)
    {
        return v / mag(v);
    }

    template <Arithmetic T>
    T dist(const vec2<T>& a, const vec2<T>& b)
    {
        return mag(a - b);
    }

    template <Arithmetic T>
    constexpr T dist_sq(const vec2<T>& a, const vec2<T>& b)
    {
        return mag_sq(a - b);
    }

    /**
	*\brief Rotate the 2D vector
	*
	*\tparam T Type of the vector
	*\param v Vector to rotate
	*\param theta Angle to rotate by. Must be in radians
	*\return vec2Imp<T> 
	*/
    template <std::floating_point T, std::convertible_to<T> T_>
    vec2<T> rotate(const vec2<T>& v, T_ theta)
    {
        using std::sin, std::cos;
        return vec2<T>{v[0] * cos(theta) - v[1] * sin(theta), v[0] * sin(theta) + v[1] * sin(theta)};
    }

    /**
	*\brief Linearly interpolate two vectors
	*
	*\tparam T Type of the vector
	*\param a first vector (x=0.0)
	*\param b second vector (x=1.0)
	*\param x value of interpolation
	*\return constexpr vec2Imp<T> 
	*/
    template <Arithmetic T, std::convertible_to<T> T_>
    constexpr vec2<T> lerp(const vec2<T>& a, const vec2<T>& b, T_ x)
    {
        return (x * b) + ((1.0 - x) * a);
    }
} // namespace Raychel

#endif // !RAYCHEL_VEC2_H
