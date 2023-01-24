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

#include <cmath>
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
        explicit ColorBase(T_ v) : Base{v, v, v}
        {}

        constexpr auto& r()
        {
            return data_[0];
        }

        [[nodiscard]] constexpr const auto& r() const
        {
            return data_[0];
        }

        constexpr auto& g()
        {
            return data_[1];
        }

        [[nodiscard]] constexpr const auto& g() const
        {
            return data_[1];
        }

        constexpr auto& b()
        {
            return data_[2];
        }

        [[nodiscard]] constexpr const auto& b() const
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

    template <std::floating_point T>
    constexpr T luminance(const basic_color<T>& c)
    {
        //taken from https://www.w3.org/WAI/GL/wiki/Relative_luminance
        constexpr basic_color<T> luminance_coefficients{.212655, .715158, .072187};

        return (c[0] * luminance_coefficients[0]) + (c[1] * luminance_coefficients[1]) + (c[2] * luminance_coefficients[2]);
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
        const u8 r = (hex >> 16U) & 0xFFU;
        const u8 g = (hex >> 8U) & 0xFFU;
        const u8 b = hex & 0xFFU;

        return convert_color<T>(basic_color<u8>{r, g, b});
    }

    template <Arithmetic T>
    basic_color<T> color_from_temperature(std::uint32_t _temp)
    {
        // Thank you to Tanner Helland at https://tannerhelland.com/2012/09/18/convert-temperature-rgb-algorithm-code.html
        using u8 = std::uint8_t;

        const auto temperature = static_cast<double>(std::clamp<std::uint32_t>(_temp, 1'000, 40'000)) / 100.;

        const auto red = [=]() -> u8 {
            if (temperature <= 66.) {
                return 255;
            }
            auto red = 329.698727446 * std::pow(temperature - 60, -.1332047592);
            red = std::clamp(red, 0., 255.);
            return static_cast<u8>(red);
        }();

        const auto green = [=]() -> u8 {
            if (temperature <= 66.0) {
                auto green = 99.4708025861 * std::log(temperature) - 161.1195681661;
                green = std::clamp(green, 0., 255.);
                return static_cast<u8>(green);
            }
            auto green = 288.1221695283 * std::pow(temperature - 60., -.0755148492);
            green = std::clamp(green, 0., 255.);
            return static_cast<u8>(green);
        }();

        const auto blue = [=]() -> u8 {
            if (temperature >= 66) {
                return 255;
            }
            if (temperature <= 19) {
                return 0;
            }

            auto blue = 138.5177312231 * std::log(temperature - 10.) - 305.0447927307;
            blue = std::clamp(blue, 0., 255.);
            return static_cast<u8>(blue);
        }();

        return convert_color<T>(basic_color<u8>{red, green, blue});
    }

} // namespace Raychel

#endif /*!RAYCHEL_COLOR_H*/
