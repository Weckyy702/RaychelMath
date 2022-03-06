/**
*\file math.h
*\author weckyy702 (weckyy702@gmail.com)
*\brief Main include header for RaychelMath library
*\date 2021-06-15
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
#ifndef RAYCHEL_MATH_H
#define RAYCHEL_MATH_H

#include <cmath>
#include <cstddef>
#include <type_traits>
#include "RaychelCore/Raychel_assert.h"
#include "concepts.h"
#include "equivalent.h"

namespace Raychel {

    template <Arithmetic _number>
    constexpr _number sq(_number x)
    {
        return x * x;
    }

    /**
	*\brief Linearly interpolate between two numbers
	*
	*\tparam _number Type of number to interpolate. Must be arithmetic
	*\param a first number (x=0.0)
	*\param b second number (x=1.0)
	*\param x value of interpolation
	*\return _number the interpolated number
	*/
    template <Arithmetic _number, std::floating_point interp_t>
    constexpr _number lerp(_number a, _number b, interp_t x)
    {
        return (x * b) + ((1.0 - x) * a);
    }

    template <std::integral _integral>
    constexpr _integral bit(size_t shift)
    {
        RAYCHEL_ASSERT(shift < (sizeof(_integral) * 8));
        return static_cast<_integral>(1U << shift);
    }

    /**
	*\brief Get number of digits in a number
	*
	*\param num The number
    *\param base base for the digit calculation
	*\return constexpr int 
	*/
    template <std::integral T>
    constexpr int numDigits(T num, std::size_t base = 10U)
    {
        //Hope computers can never represent integers with more than 2 billion digits ;)
        int digits = 0;
        do {
            digits++;
            num /= base;
        } while (num != 0);

        return digits;
    }

    template <std::floating_point Real>
    constexpr bool is_integer(Real num) noexcept
    {
        return equivalent<Real>(static_cast<Real>(std::fmod(num, 1)), 0);
    }

    template <std::integral Num>
    constexpr bool is_integer(Num /*unused*/) noexcept
    {
        return true;
    }

} // namespace Raychel
#endif //!RAYCHEL_MATH_H