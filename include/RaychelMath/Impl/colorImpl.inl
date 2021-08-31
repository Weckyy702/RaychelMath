/**
*\file colorImpl.inl
*\author weckyy702 (weckyy702@gmail.com)
*\brief Implementation for RGB colors
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
#ifndef RAYCHEL_COLOR_IMP
#define RAYCHEL_COLOR_IMP

#include <limits>

#include "../color.h"
#include "../vec2.h"
#include "../vec3.h"

namespace Raychel {

    namespace details {

        template <Arithmetic T>
        constexpr colorImp<T> ensureValidColor(const colorImp<T>& c) noexcept
        {
            using std::clamp, std::max;
            using vt = typename colorImp<T>::value_type;

            if constexpr (std::is_floating_point_v<vt>) {
                return {clamp<vt>(c.r, 0, 1.0), clamp<vt>(c.g, 0, 1.0), clamp<vt>(c.b, 0, 1.0)};
            }

            //assuming 2's complement, all integral types wrap around on overflow, so we don't need to clamp off anything larger than std::numeric_limits<T>::max()
            return {max<vt>(c.r, 0), max<vt>(c.g, 0), max<vt>(c.b, 0)};
        }

        template <Arithmetic T, Arithmetic To>
        constexpr colorImp<To> convert_float(const colorImp<T>& _c) noexcept
        {
            const auto c = ensureValidColor(_c);
            if constexpr (std::is_integral_v<To>) {
                constexpr auto max = std::numeric_limits<To>::max();

                return colorImp<To>{static_cast<To>(c.r * max), static_cast<To>(c.g * max), static_cast<To>(c.b * max)};
            } else {
                return colorImp<To>(c.r, c.g, c.b);
            }
        }

        template <Arithmetic T, Arithmetic To>
        constexpr colorImp<To> convert_integral(const colorImp<T>& _c) noexcept
        {
            const auto c = ensureValidColor(_c);

            if constexpr (std::is_floating_point_v<To>) {
                constexpr To max = std::numeric_limits<T>::max();

                return colorImp<To>(c.r / max, c.g / max, c.b / max);
            }
            return colorImp<To>(c.r, c.g, c.b);
        }
    } // namespace details

    template <Arithmetic T>
    constexpr colorImp<T>::operator const value_type*() const noexcept
    {
        //NOTE: this might invoke UB if the compiler inserts padding in between r, g and b
        return &r;
    }

    template <Arithmetic T>
    constexpr colorImp<T>::colorImp(const vec3& v) noexcept
    {
        using std::abs;
        r = abs(v.x);
        g = abs(v.y);
        b = abs(v.z);
    }

    template <Arithmetic T>
    constexpr colorImp<T>::colorImp(const vec2& v) noexcept
    {
        using std::abs;
        r = abs(v.x);
        g = abs(v.y);
        b = 0;
    }

    template <Arithmetic T>
    template <Arithmetic To>
    constexpr colorImp<To> colorImp<T>::to() const noexcept
    {
        using vt = typename colorImp<To>::value_type;

        if constexpr (std::is_floating_point_v<value_type>) {
            return details::convert_float<value_type, vt>(*this);
        } else {
            return details::convert_integral<value_type, vt>(*this);
        }
    }

    template <Arithmetic T>
    constexpr colorImp<T>& colorImp<T>::operator=(const vec3& v) noexcept
    {
        r = abs(v.x);
        g = abs(v.y);
        b = abs(v.z);

        return *this;
    }

    template <Arithmetic T>
    constexpr colorImp<T>& colorImp<T>::operator=(const vec2& v) noexcept
    {
        r = abs(v.x);
        g = abs(v.y);
        b = 0;
        return *this;
    }

    template <Arithmetic T>
    constexpr colorImp<T>& colorImp<T>::operator+=(const colorImp& c) noexcept
    {
        r += c.r;
        g += c.g;
        b += c.b;
        return *this;
    }

    template <Arithmetic T>
    constexpr colorImp<T>& colorImp<T>::operator-=(const colorImp& c) noexcept
    {
        r -= c.r;
        g -= c.g;
        b -= c.b;
        return *this;
    }

    template <Arithmetic T>
    constexpr colorImp<T>& colorImp<T>::operator*=(value_type s) noexcept
    {
        r *= s;
        g *= s;
        b *= s;
        return *this;
    }

    template <Arithmetic T>
    constexpr colorImp<T>& colorImp<T>::operator/=(const colorImp& c) noexcept
    {
        r /= c.r;
        g /= c.g;
        b /= c.b;
        return *this;
    }

    template <Arithmetic T>
    constexpr colorImp<T>& colorImp<T>::operator*=(const colorImp& c) noexcept
    {
        r *= c.r;
        g *= c.g;
        b *= c.b;
        return *this;
    }

    template <Arithmetic T>
    constexpr colorImp<T>& colorImp<T>::operator/=(value_type s) noexcept
    {
        r /= s;
        g /= s;
        b /= s;
        return *this;
    }

    template <Arithmetic T>
    constexpr colorImp<T> colorImp<T>::from_rgb(std::uint8_t r, std::uint8_t g, std::uint8_t b) noexcept
    {
        return colorImp<uint8_t>{r, g, b}.to<T>();
    }

    template <Arithmetic T>
    constexpr colorImp<T> colorImp<T>::from_hex(std::uint32_t hex) noexcept
    {
        const auto r = static_cast<std::uint8_t>((hex >> 16U) & 0xFFU);
        const auto g = static_cast<std::uint8_t>((hex >> 8U) & 0xFFU);
        const auto b = static_cast<std::uint8_t>(hex & 0xFFU);

        return from_rgb(r, g, b);
    }

    template <Arithmetic T>
    std::ostream& operator<<(std::ostream& os, const colorImp<T>& c)
    {
        return os << "{ " << c.r << ", " << c.g << ", " << c.b << " }";
    }

    template <Arithmetic T>
    constexpr colorImp<T> operator-(const colorImp<T>& c) noexcept
    {
        using value_type = typename colorImp<T>::value_type;

        if constexpr (std::is_floating_point_v<value_type>) {
            return details::ensureValidColor(colorImp<value_type>(1.0F - c.r, 1.0F - c.g, 1.0F - c.b));
        } else {
            constexpr auto max = std::numeric_limits<value_type>::max();
            return details::ensureValidColor(colorImp<value_type>(max - c.r, max - c.g, max - c.b));
        }
    }

    template <Arithmetic T>
    constexpr colorImp<T> operator+(const colorImp<T>& a, const colorImp<T>& b) noexcept
    {
        return colorImp<T>(a.r + b.r, a.g + b.g, a.b + b.b);
    }

    template <Arithmetic T>
    constexpr colorImp<T> operator-(const colorImp<T>& a, const colorImp<T>& b) noexcept
    {
        return colorImp<T>(a.r - b.r, a.g - b.g, a.b - b.b);
    }

    template <Arithmetic T>
    constexpr colorImp<T> operator*(const colorImp<T>& a, const colorImp<T>& b) noexcept
    {
        return colorImp<T>(a.r * b.r, a.g * b.g, a.b * b.b);
    }

    template <Arithmetic T>
    constexpr colorImp<T> operator*(const colorImp<T>& c, T s) noexcept
    {
        return colorImp<T>(c.r * s, c.g * s, c.b * s);
    }

    template <Arithmetic T>
    constexpr colorImp<T> operator/(const colorImp<T>& a, const colorImp<T>& b) noexcept
    {
        return colorImp<T>(a.r / b.r, a.g / b.g, a.b / b.b);
    }

    template <Arithmetic T>
    constexpr colorImp<T> operator/(const colorImp<T>& c, T s) noexcept
    {
        return colorImp<T>(c.r / s, c.g / s, c.b / s);
    }

    template <Arithmetic T>
    constexpr bool operator==(const colorImp<T>& a, const colorImp<T>& b) noexcept
    {
#ifdef RAYCHEL_LOGICALLY_EQUAL
        return equivalent(a.r, b.r) && equivalent(a.g, b.g) && equivalent(a.b, b.b);
#else
        return (a.r == b.r) && (a.g == b.g) && (a.b == b.b);
#endif
    }

    template <Arithmetic T>
    constexpr colorImp<bool> operator<(const colorImp<T>& a, const colorImp<T>& b) noexcept
    {
        return {a.r < b.r, a.g < b.g, a.b < b.b};
    }

    template <Arithmetic T>
    constexpr colorImp<bool> operator<=(const colorImp<T>& a, const colorImp<T>& b) noexcept
    {
        return {a.r <= b.r, a.g <= b.g, a.b <= b.b};
    }

    template <Arithmetic T>
    constexpr colorImp<bool> operator>(const colorImp<T>& a, const colorImp<T>& b) noexcept
    {
        return {a.r > b.r, a.g > b.g, a.b > b.b};
    }

    template <Arithmetic T>
    constexpr colorImp<bool> operator>=(const colorImp<T>& a, const colorImp<T>& b) noexcept
    {
        return {a.r >= b.r, a.g >= b.g, a.b >= b.b};
    }

    template <Arithmetic T>
    constexpr colorImp<T> max(const colorImp<T>& a, const colorImp<T>& b) noexcept
    {
        using std::max;
        return colorImp<T>(max(a.r, b.r), max(a.g, b.g), max(a.b, b.b));
    }

    template <Arithmetic T>
    constexpr colorImp<T> min(const colorImp<T>& a, const colorImp<T>& b) noexcept
    {
        using std::min;
        return colorImp<T>(min(a.r, b.r), min(a.g, b.g), min(a.b, b.b));
    }

    template <Arithmetic T>
    constexpr T brightness(const colorImp<T>& c) noexcept
    {
        return (c.r + c.g + c.b) / T(3.0);
    }
} // namespace Raychel

#endif /*RAYCHEL_COLOR_IMP*/
