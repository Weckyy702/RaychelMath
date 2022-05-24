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

#include "Tuple.h"

#include <limits>
#include <numeric>
#include <ratio>

namespace Raychel {

    struct ColorTag
    {};

    template <Arithmetic T>
    struct ColorBase : public TupleBase<T, 3>
    {
        using Base = TupleBase<T, 3>;
        using Base::Base, Base::data_, Base::get;

        template <std::convertible_to<T> T_>
        ColorBase(T_ v) : Base{v, v, v}
        {}

        constexpr auto& r()
        {
            return data_[0];
        }

        constexpr const auto& r() const
        {
            return data_[0];
        }

        constexpr auto& g()
        {
            return data_[1];
        }

        constexpr const auto& g() const
        {
            return data_[1];
        }

        constexpr auto& b()
        {
            return data_[2];
        }

        constexpr const auto& b() const
        {
            return data_[2];
        }
    };

    template <Arithmetic T>
    struct TupleTraits<T, 3, ColorTag>
    {
        using Base = ColorBase<T>;
    };

    template <Arithmetic T>
    using basic_color = Tuple<T, 3, ColorTag>;

    template <Arithmetic T>
    constexpr basic_color<T>& operator*=(basic_color<T>& a, const basic_color<T>& b)
    {
        for (std::size_t i{0}; i != 3; ++i) {
            a[i] = a[i] * b[i];
        }
        return a;
    }

    template <Arithmetic T>
    constexpr basic_color<T> operator*(const basic_color<T>& a, const basic_color<T>& b)
    {
        auto res{a};
        res *= b;
        return res;
    }

    template <Arithmetic T>
    constexpr T brightness(const basic_color<T>& c)
    {
        return (c[0] + c[1] + c[2]) / 3;
    }

    namespace details {
        template <std::integral From, std::integral To>
        constexpr basic_color<To> convert_color_helper(const basic_color<From>& c)
        {
            constexpr auto to_max = std::numeric_limits<To>::max();
            constexpr auto from_max = std::numeric_limits<From>::max();

            if constexpr (to_max > from_max) {
                constexpr To ratio = to_max / from_max;
                return basic_color<To>{
                    static_cast<To>(c[0]) * ratio, static_cast<To>(c[1]) * ratio, static_cast<To>(c[2]) * ratio};
            }
            //TODO: find a better way to dodge lossy floating point arithmetic
            constexpr auto ratio = static_cast<double>(to_max) / from_max;
            return basic_color<To>{static_cast<To>(c[0] * ratio), static_cast<To>(c[1] * ratio), static_cast<To>(c[2] * ratio)};
        }

        template <std::floating_point From, std::floating_point To>
        constexpr basic_color<To> convert_color_helper(const basic_color<From>& c)
        {
            return basic_color<To>{c[0], c[1], c[2]};
        }

        template <std::floating_point From, std::integral To>
        constexpr basic_color<To> convert_color_helper(const basic_color<From>& c)
        {
            using std::clamp;
            constexpr auto max = std::numeric_limits<To>::max();
            return basic_color<To>{clamp<From>(c[0], 0, 1) * max, clamp<From>(c[1], 0, 1) * max, clamp<From>(c[2], 0, 1) * max};
        }

        template <std::integral From, std::floating_point To>
        constexpr basic_color<To> convert_color_helper(const basic_color<From>& c)
        {
            constexpr auto max = static_cast<To>(std::numeric_limits<From>::max());
            return basic_color<To>{static_cast<To>(c[0]) / max, static_cast<To>(c[1]) / max, static_cast<To>(c[2]) / max};
        }
    } // namespace details

    template <Arithmetic To, std::convertible_to<To> From>
    constexpr basic_color<To> convert_color(const basic_color<From>& c)
    {
        if constexpr (std::is_same_v<From, To>) {
            return c;
        }
        return details::convert_color_helper<From, To>(c);
    }

    template <Arithmetic T>
    constexpr basic_color<T> color_from_rgb(std::uint8_t r, std::uint8_t g, std::uint8_t b)
    {
        return convert_color<T>(basic_color<std::uint8_t>{r, g, b});
    }

    template <Arithmetic T>
    constexpr basic_color<T> color_from_hex(std::uint32_t hex)
    {
        using u8 = std::uint8_t;
        const u8 r = (hex >> 16) & 0xFFU;
        const u8 g = (hex >> 8) & 0xFFU;
        const u8 b = hex & 0xFFU;

        return convert_color<T>(basic_color<u8>{r, g, b});
    }

} // namespace Raychel

#endif /*!RAYCHEL_COLOR_H*/
