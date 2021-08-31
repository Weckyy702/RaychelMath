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

#include "forward.h"

namespace Raychel {

    /**
	*\brief 2D vector
	*
	*\tparam _number Type of the vector. Must be arithmetic
	*/
    template <Arithmetic _number>
    struct vec2Imp
    {
        using value_type = std::remove_cvref_t<_number>;

    private:
        using vec3 = vec3Imp<value_type>;
        using color = colorImp<value_type>;

    public:
        constexpr vec2Imp() = default;

        explicit constexpr vec2Imp(value_type _x) : x(_x), y(0)
        {}

        constexpr vec2Imp(value_type _x, value_type _y) : x(_x), y(_y)
        {}

        /**
		*\brief Convert the vector to another vector
		*
		*\tparam To Type of the converted vector
		*\return vec2Imp<To> 
		*/
        template <Arithmetic To>
        constexpr vec2Imp<To> to() const;

        explicit constexpr vec2Imp(const vec3&);
        explicit constexpr vec2Imp(const color&);

        constexpr vec2Imp& operator=(const vec3&);
        constexpr vec2Imp& operator=(const color&);

        constexpr vec2Imp& operator+=(const vec2Imp&);
        constexpr vec2Imp& operator-=(const vec2Imp&);
        constexpr vec2Imp& operator*=(value_type);
        constexpr vec2Imp& operator*=(const vec2Imp&);
        constexpr vec2Imp& operator/=(value_type);
        constexpr vec2Imp& operator/=(const vec2Imp&);
        vec2Imp& operator%=(const vec2Imp&);

        value_type x{0}, y{0};
    };

    template <Arithmetic T>
    std::ostream& operator<<(std::ostream&, const vec2Imp<T>&);

    template <Arithmetic T>
    constexpr vec2Imp<T> operator-(const vec2Imp<T>&);

    template <Arithmetic T>
    constexpr vec2Imp<T> operator+(const vec2Imp<T>&, const vec2Imp<T>&);

    template <Arithmetic T>
    constexpr vec2Imp<T> operator-(const vec2Imp<T>&, const vec2Imp<T>&);

    template <Arithmetic T>
    constexpr vec2Imp<T> operator*(const vec2Imp<T>&, const vec2Imp<T>&);

    template <Arithmetic T>
    constexpr vec2Imp<T> operator*(const vec2Imp<T>&, T);

    template <Arithmetic T>
    constexpr vec2Imp<T> operator*(T s, const vec2Imp<T>& v)
    {
        return v * s;
    }

    template <Arithmetic T>
    constexpr vec2Imp<T> operator/(const vec2Imp<T>&, const vec2Imp<T>&);

    template <Arithmetic T>
    constexpr vec2Imp<T> operator/(const vec2Imp<T>&, T);

    template <Arithmetic T>
    vec2Imp<T> operator%(const vec2Imp<T>&, const vec2Imp<T>&);

    template <Arithmetic T>
    constexpr bool operator==(const vec2Imp<T>&, const vec2Imp<T>&);

    template <Arithmetic T>
    constexpr bool operator!=(const vec2Imp<T>& a, const vec2Imp<T>& b)
    {
        return !(a == b);
    }

    template <Arithmetic T>
    constexpr vec2Imp<bool> operator<(const vec2Imp<T>&, const vec2Imp<T>&);

    template <Arithmetic T>
    constexpr vec2Imp<bool> operator<=(const vec2Imp<T>&, const vec2Imp<T>&);

    template <Arithmetic T>
    constexpr vec2Imp<bool> operator>(const vec2Imp<T>&, const vec2Imp<T>&);

    template <Arithmetic T>
    constexpr vec2Imp<bool> operator>=(const vec2Imp<T>&, const vec2Imp<T>&);

    template <Arithmetic T>
    constexpr T dot(const vec2Imp<T>&, const vec2Imp<T>&);

    template <Arithmetic T>
    T mag(const vec2Imp<T>&);

    template <Arithmetic T>
    constexpr T magSq(const vec2Imp<T>&);

    template <std::floating_point T>
    vec2Imp<T> normalize(const vec2Imp<T>&);

    template <Arithmetic T>
    vec2Imp<T> abs(const vec2Imp<T>&);

    template <Arithmetic T>
    vec2Imp<T> max(const vec2Imp<T>&, const vec2Imp<T>&);

    template <Arithmetic T>
    vec2Imp<T> min(const vec2Imp<T>&, const vec2Imp<T>&);

    template <Arithmetic T>
    vec2Imp<T> sin(const vec2Imp<T>&);

    template <Arithmetic T>
    vec2Imp<T> cos(const vec2Imp<T>&);

    template <Arithmetic T>
    vec2Imp<T> pow(const vec2Imp<T>&, T);

    template <Arithmetic T>
    vec2Imp<T> pow(const vec2Imp<T>&, const vec2Imp<T>&);

    template <Arithmetic T>
    T dist(const vec2Imp<T>&, const vec2Imp<T>&);

    template <Arithmetic T>
    constexpr T distSq(const vec2Imp<T>&, const vec2Imp<T>&);

    /**
	*\brief Rotate the 2D vector
	*
	*\tparam T Type of the vector
	*\param v Vector to rotate
	*\param theta Angle to rotate by. Must be in radians
	*\return vec2Imp<T> 
	*/
    template <Arithmetic T>
    vec2Imp<T> rotate(const vec2Imp<T>& v, T theta);

    /**
	*\brief Linearly interpolate two vectors
	*
	*\tparam T Type of the vector
	*\param a first vector (x=0.0)
	*\param b second vector (x=1.0)
	*\param x value of interpolation
	*\return constexpr vec2Imp<T> 
	*/
    template <Arithmetic T>
    constexpr vec2Imp<T> lerp(const vec2Imp<T>& a, const vec2Imp<T>& b, long double x)
    {
        return (x * b) + ((1.0 - x) * a);
    }
} // namespace Raychel

#endif // !RAYCHEL_VEC2_H
