/**
*\file color.h
*\author weckyy702 (weckyy702@gmail.com)
*\brief Header file for RGB colors
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
#ifndef RAYCHEL_COLOR_H
#define RAYCHEL_COLOR_H

#include "forward.h"

namespace Raychel {

    /**
	*\brief RGB color value
	*
	*\tparam _number Type of color value. Must be arithmetic
	*/
    template <Arithmetic _number>
    struct colorImp
    {
        using value_type = std::remove_cvref_t<_number>;

    private:
        using vec3 = vec3Imp<value_type>;
        using vec2 = vec2Imp<value_type>;

    public:
        constexpr colorImp() noexcept = default;

        constexpr explicit colorImp(value_type _b) noexcept : r(_b), g(_b), b(_b)
        {}

        constexpr colorImp(value_type _r, value_type _g) noexcept : r(_r), g(_g), b(0)
        {}

        constexpr colorImp(value_type _r, value_type _g, value_type _b) noexcept : r(_r), g(_g), b(_b)
        {}

        /**
		*\brief Convert the color to another color of type To. The color will be clamped before conversion
		*
		*\tparam To Type of the converted color
		*\return colorImp<_To> 
		*/
        template <Arithmetic To>
        constexpr colorImp<To> to() const noexcept;

        /**
		*\brief Convert the color to a pointer-to-red. For functions that need colors as arrays
		*
		*\return const value_type* the value array in RGB order
		*/
        constexpr explicit operator const value_type*() const noexcept;

        constexpr explicit colorImp(const vec3&) noexcept;
        constexpr explicit colorImp(const vec2&) noexcept;

        constexpr colorImp& operator=(const vec3&) noexcept;
        constexpr colorImp& operator=(const vec2&) noexcept;

        constexpr colorImp& operator+=(const colorImp&) noexcept;
        constexpr colorImp& operator-=(const colorImp&) noexcept;
        constexpr colorImp& operator*=(value_type) noexcept;
        constexpr colorImp& operator*=(const colorImp&) noexcept;
        constexpr colorImp& operator/=(const colorImp&) noexcept;
        constexpr colorImp& operator/=(value_type) noexcept;

        /**
        * \brief create color from 8-bit RGB values
        * 
        * \param r red value [0-255]
        * \param g green value [0-255]
        * \param b blue value [0-255]
        * \return colorImp
        */
        static constexpr colorImp from_rgb(std::uint8_t r, std::uint8_t g, std::uint8_t b) noexcept;

        /**
        * \brief create color from 24-bit HEX value
        * 
        * \param hex hex value in the format xxRRGGBB
        * \return colorImp
        */
        static constexpr colorImp from_hex(std::uint32_t hex) noexcept;

        value_type r{0}, g{0}, b{0};
    };

    template <Arithmetic T>
    std::ostream& operator<<(std::ostream& os, const colorImp<T>& c);

    template <Arithmetic T>
    constexpr colorImp<T> operator-(const colorImp<T>&) noexcept;

    template <Arithmetic T>
    constexpr colorImp<T> operator+(const colorImp<T>&, const colorImp<T>&) noexcept;

    template <Arithmetic T>
    constexpr colorImp<T> operator-(const colorImp<T>&, const colorImp<T>&) noexcept;

    template <Arithmetic T>
    constexpr colorImp<T> operator*(const colorImp<T>&, const colorImp<T>&) noexcept;

    template <Arithmetic T>
    constexpr colorImp<T> operator*(const colorImp<T>&, T) noexcept;

    template <Arithmetic T>
    constexpr colorImp<T> operator*(T s, const colorImp<T>& v) noexcept
    {
        return v * s;
    }

    template <Arithmetic T>
    constexpr colorImp<T> operator/(const colorImp<T>&, const colorImp<T>&) noexcept;

    template <Arithmetic T>
    constexpr colorImp<T> operator/(const colorImp<T>&, T) noexcept;

    template <Arithmetic T>
    constexpr bool operator==(const colorImp<T>&, const colorImp<T>&) noexcept;

    template <Arithmetic T>
    constexpr bool operator!=(const colorImp<T>& a, const colorImp<T>& b) noexcept
    {
        return !(a == b);
    }

    template <Arithmetic T>
    constexpr colorImp<bool> operator<(const colorImp<T>&, const colorImp<T>&) noexcept;

    template <Arithmetic T>
    constexpr colorImp<bool> operator<=(const colorImp<T>&, const colorImp<T>&) noexcept;

    template <Arithmetic T>
    constexpr colorImp<bool> operator>(const colorImp<T>&, const colorImp<T>&) noexcept;

    template <Arithmetic T>
    constexpr colorImp<bool> operator>=(const colorImp<T>&, const colorImp<T>&) noexcept;

    template <Arithmetic T>
    constexpr colorImp<T> max(const colorImp<T>&, const colorImp<T>&) noexcept;

    template <Arithmetic T>
    constexpr colorImp<T> min(const colorImp<T>&, const colorImp<T>&) noexcept;

    template <Arithmetic T>
    constexpr T brightness(const colorImp<T>&) noexcept;
} // namespace Raychel

#endif /*!RAYCHEL_COLOR_H*/
