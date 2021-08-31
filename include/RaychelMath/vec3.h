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

#include "forward.h"

//TODO: make all non-constexpr functions constexpr again once the compiler finds an answer to sqrt(x) at compile time

namespace Raychel {

    /**
	*\brief 3D vector
	*
	*\tparam _number Type of the vector. Must be arithmetic
	*/
    template <Arithmetic _number>
    struct vec3Imp
    {
        using value_type = std::remove_cvref_t<_number>;

    private:
        using vec2 = vec2Imp<value_type>;
        using color = colorImp<value_type>;

    public:
        constexpr vec3Imp() noexcept = default;

        explicit constexpr vec3Imp(value_type _x) noexcept : x(_x)
        {}

        constexpr vec3Imp(value_type _x, value_type _y) noexcept : x(_x), y(_y)
        {}

        constexpr vec3Imp(value_type _x, value_type _y, value_type _z) noexcept : x(_x), y(_y), z(_z)
        {}

        /**
		*\brief Convert the vector to the same vector of another type
		*
		*\tparam To Type of the converted vector
		*\return vec3Imp<To> 
		*/
        template <Arithmetic To>
        constexpr vec3Imp<To> to() const noexcept;

        constexpr explicit vec3Imp(const vec2&) noexcept;
        constexpr explicit vec3Imp(const color&) noexcept;

        constexpr vec3Imp& operator=(const vec2&) noexcept;
        constexpr vec3Imp& operator=(const color&) noexcept;

        constexpr vec3Imp& operator+=(const vec3Imp&) noexcept;
        constexpr vec3Imp& operator-=(const vec3Imp&) noexcept;
        constexpr vec3Imp& operator*=(value_type) noexcept;
        constexpr vec3Imp& operator*=(const vec3Imp&) noexcept;
        constexpr vec3Imp& operator/=(value_type) noexcept;
        constexpr vec3Imp& operator/=(const vec3Imp&) noexcept;
        constexpr vec3Imp& operator%=(const vec3Imp&) noexcept;

        value_type x{0}, y{0}, z{0};
    };

    template <Arithmetic T>
    std::ostream& operator<<(std::ostream&, const vec3Imp<T>&);

    template <Arithmetic T>
    constexpr vec3Imp<T> operator-(const vec3Imp<T>&) noexcept;

    template <Arithmetic T>
    constexpr vec3Imp<T> operator+(const vec3Imp<T>&, const vec3Imp<T>&) noexcept;

    template <Arithmetic T>
    constexpr vec3Imp<T> operator-(const vec3Imp<T>&, const vec3Imp<T>&) noexcept;

    template <Arithmetic T>
    constexpr vec3Imp<T> operator*(const vec3Imp<T>&, const vec3Imp<T>&) noexcept;

    template <Arithmetic T>
    constexpr vec3Imp<T> operator*(const vec3Imp<T>&, T) noexcept;

    template <Arithmetic T>
    constexpr vec3Imp<T> operator*(T s, const vec3Imp<T>& v) noexcept
    {
        return v * s;
    }

    template <Arithmetic T>
    constexpr vec3Imp<T> operator/(const vec3Imp<T>&, const vec3Imp<T>&) noexcept;

    template <Arithmetic T>
    constexpr vec3Imp<T> operator/(const vec3Imp<T>&, T) noexcept;

    //TODO: make these constexpr once the compiler finally finds a way to answer x % y at compile time
    template <Arithmetic T>
    vec3Imp<T> operator%(const vec3Imp<T>&, const vec3Imp<T>&) noexcept;

    template <Arithmetic T>
    vec3Imp<T> operator%(const vec3Imp<T>&, T) noexcept;

    template <Arithmetic T>
    constexpr bool operator==(const vec3Imp<T>&, const vec3Imp<T>&) noexcept;

    template <Arithmetic T>
    constexpr bool operator!=(const vec3Imp<T>& a, const vec3Imp<T>& b) noexcept
    {
        return !(a == b);
    }

    template <Arithmetic T>
    constexpr vec3Imp<bool> operator<(const vec3Imp<T>&, const vec3Imp<T>&) noexcept;

    template <Arithmetic T>
    constexpr vec3Imp<bool> operator<=(const vec3Imp<T>&, const vec3Imp<T>&) noexcept;

    template <Arithmetic T>
    constexpr vec3Imp<bool> operator>(const vec3Imp<T>&, const vec3Imp<T>&) noexcept;

    template <Arithmetic T>
    constexpr vec3Imp<bool> operator>=(const vec3Imp<T>&, const vec3Imp<T>&) noexcept;

    template <Arithmetic T>
    constexpr T dot(const vec3Imp<T>&, const vec3Imp<T>&) noexcept;

    //TODO: make this one constexpr aswell
    template <Arithmetic T>
    T mag(const vec3Imp<T>&) noexcept;

    template <Arithmetic T>
    constexpr T magSq(const vec3Imp<T>&) noexcept;

    template <Arithmetic T>
    T dist(const vec3Imp<T>&, const vec3Imp<T>&) noexcept;

    template <Arithmetic T>
    constexpr T distSq(const vec3Imp<T>&, const vec3Imp<T>&) noexcept;

    template <Arithmetic T>
    vec3Imp<T> max(const vec3Imp<T>&, const vec3Imp<T>&) noexcept;

    template <Arithmetic T>
    vec3Imp<T> min(const vec3Imp<T>&, const vec3Imp<T>&) noexcept;

    //normalizing vectors only makes sense for floating-point types
    template <std::floating_point T>
    vec3Imp<T> normalize(const vec3Imp<T>&) noexcept;

    template <Arithmetic T>
    requires std::is_signed_v<T> vec3Imp<T> abs(const vec3Imp<T>&)
    noexcept;

    template <std::floating_point T>
    vec3Imp<T> sin(const vec3Imp<T>&) noexcept;

    template <std::floating_point T>
    vec3Imp<T> cos(const vec3Imp<T>&) noexcept;

    template <Arithmetic T>
    constexpr vec3Imp<T> cross(const vec3Imp<T>&, const vec3Imp<T>&) noexcept;

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
    constexpr vec3Imp<T> lerp(const vec3Imp<T>& a, const vec3Imp<T>& b, T) noexcept;

} // namespace Raychel

#endif /*!RAYCHEL_VEC3_H*/
