/**
* \file TupleTraits.h
* \author Weckyy702 (weckyy702@gmail.com)
* \brief Header file for TupleTraits class
* \date 2022-05-23
*
* MIT License
* Copyright (c) [2022] [Weckyy702 (weckyy702@gmail.com | https://github.com/Weckyy702)]
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
*/
#ifndef RAYCHEL_TUPLE_TRAITS_H
#define RAYCHEL_TUPLE_TRAITS_H

#include "concepts.h"

#include <algorithm>
#include <array>
#include <iostream>

namespace Raychel {

    template <Arithmetic T, std::size_t N>
    requires(N != 0U) struct TupleBase
    {
    public:
        template <std::convertible_to<T>... Us>
        constexpr explicit TupleBase(Us&&... us) : data_{static_cast<T>(us)...}
        {}

        template <std::size_t N_>
        constexpr TupleBase(const std::array<T, N_>& values)
        {
            if constexpr (N_ > N) {
                std::copy_n(values.begin(), N, data_.begin());
            } else {
                data_.fill(0);
                std::copy_n(values.begin(), N_, data_.begin());
            }
        }

        constexpr T& operator[](std::size_t i)
        {
            if (!std::is_constant_evaluated()) {
                RAYCHEL_ASSERT(i < N);
            }
            return data_[i];
        }

        constexpr const T& operator[](std::size_t i) const
        {
            if (!std::is_constant_evaluated()) {
                RAYCHEL_ASSERT(i < N);
            }
            return data_[i];
        }

        template <std::size_t I>
        requires(I < N) constexpr T get() const
        {
            return data_[I];
        }

        auto begin() noexcept
        {
            return data_.begin();
        }

        auto begin() const noexcept
        {
            return data_.begin();
        }

        auto end() noexcept
        {
            return data_.end();
        }

        auto end() const noexcept
        {
            return data_.end();
        }

    protected:
        std::array<T, N> data_{};
    };

    template <Arithmetic T, std::size_t N>
    inline std::ostream& operator<<(std::ostream& os, const TupleBase<T, N>& obj)
    {
        os << '{';
        for (std::size_t i{0}; i != N - 1; ++i) {
            os << obj[i] << ' ';
        }
        return os << obj[N - 1] << '}';
    }

    template <Arithmetic T, std::size_t N>
    inline std::istream& operator>>(std::istream& is, TupleBase<T, N>& obj)
    {
        const auto saved_flags = is.flags();
        is.flags(std::ios_base::dec);

        bool did_fail{false};
        char control_char{};

        did_fail |= !((is >> control_char) && control_char == '{');

        for (std::size_t i{0}; i != N - 1 && !did_fail; ++i) {
            did_fail |= !(is >> obj[i]);
            did_fail |= !((is >> control_char) && (control_char == ' '));
        }

        if (!did_fail) {
            did_fail |= !(is >> obj[N - 1]);
            did_fail |= !((is >> control_char) && (control_char == '}'));
        }

        if (did_fail)
            is.setstate(std::ios_base::failbit);
        is.flags(saved_flags);
        return is;
    }

    template <Arithmetic T, std::size_t N, typename Tag>
    struct TupleTraits
    {
        using Base = TupleBase<T, N>;
    };

} // namespace Raychel

#endif //!RAYCHEL_TUPLE_TRAITS_H
