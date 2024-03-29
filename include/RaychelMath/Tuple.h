/**
* \file Tuple.h
* \author Weckyy702 (weckyy702@gmail.com)
* \brief Header file for Tuple class
* \date 2022-03-03
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
#ifndef RAYCHELMATH_TUPLE_H
#define RAYCHELMATH_TUPLE_H

#include "RaychelCore/Raychel_assert.h"
#include "RaychelMath/concepts.h"
#include "TupleBase.h"

#include <cstddef>
#include <iostream>
#include <tuple>
#include <type_traits>
#include <utility>

namespace Raychel {

    namespace details {
        template <std::size_t N, std::size_t Head, std::size_t... Tail>
        struct IndeciesValid
        {
            static constexpr bool value = IndeciesValid<N, Head>::value && IndeciesValid<N, Tail...>::value;
        };

        template <std::size_t N, std::size_t Head>
        struct IndeciesValid<N, Head>
        {
            static constexpr bool value = Head < N;
        };

        template <std::size_t N, std::size_t... Indecies>
        constexpr auto indecies_valid = IndeciesValid<N, Indecies...>::value;
    } // namespace details

    //Tag to identify "just a tuple" without further semantic meaning
    struct TupleTag
    {};

    //Define this struct to allow conversion between custom tuples (see vec3 and color for reference)
    template <typename FromTag, typename ToTag>
    struct tuple_convertable : std::false_type
    {};

    //Any type can convert into a regular tuple
    template <typename FromTag>
    struct tuple_convertable<FromTag, TupleTag> : std::true_type
    {};

    template <typename FromTag, typename ToTag>
    constexpr auto is_tuple_convertible_v = std::is_same_v<FromTag, ToTag> || tuple_convertable<FromTag, ToTag>::value;

    template <typename ToTag, typename FromTag>
    concept TupleConvertable = is_tuple_convertible_v<FromTag, ToTag>;

    template <Arithmetic T, std::size_t N, typename Tag = TupleTag>
        requires(N != 0)
    class Tuple : public TupleTraits<T, N, Tag>::Base
    {
        using _base = typename TupleTraits<T, N, Tag>::Base;
        using _base::data_;

        static_assert(std::is_base_of_v<TupleBase<T, N>, _base>, "Tuple base must be derived from TupleBase");

    public:
        using Base = _base;
        using Base::Base;

        template <std::size_t N_, TupleConvertable<Tag> Tag_>
            requires(N_ >= N)
        constexpr explicit operator Tuple<T, N_, Tag_>() const
        {
            return Tuple<T, N_, Tag_>{data_};
        }

        template <Arithmetic To>
            requires(std::is_convertible_v<T, To>)
        constexpr explicit operator Tuple<To, N, Tag>() const
        {
            Tuple<To, N, Tag> result;

            for (std::size_t i{}; i != N; ++i) {
                result[i] = static_cast<To>(data_[i]);
            }

            return result;
        }

        template <std::size_t N_, TupleConvertable<Tag> Tag_>
            requires(N_ < N)
        constexpr explicit operator Tuple<T, N_, Tag_>() const
        {
            return Tuple<T, N_, Tag_>{data_};
        }

        template <TupleConvertable<Tag> Tag_>
        constexpr Tuple& operator+=(const Tuple<T, N, Tag_>& x)
        {
            for (std::size_t i{0}; i != N; ++i) {
                data_[i] = data_[i] + x[i];
            }
            return *this;
        }

        template <TupleConvertable<Tag> Tag_>
        constexpr Tuple& operator-=(const Tuple<T, N, Tag_>& x)
        {
            for (std::size_t i{0}; i != N; ++i) {
                data_[i] = data_[i] - x[i];
            }
            return *this;
        }

        template <std::convertible_to<T> T_>
        constexpr Tuple& operator*=(T_ x)
        {
            for (std::size_t i{0}; i != N; ++i) {
                data_[i] = data_[i] * x;
            }
            return *this;
        }

        template <std::convertible_to<T> T_>
        constexpr Tuple& operator/=(T_ x)
        {
            for (std::size_t i{0}; i != N; ++i) {
                data_[i] = data_[i] / x;
            }
            return *this;
        }
    };

    template <Arithmetic... Ts>
    Tuple(Ts...) -> Tuple<std::common_type_t<Ts...>, sizeof...(Ts)>;

    template <Arithmetic T, std::size_t N>
    Tuple(std::array<T, N>) -> Tuple<T, N>;

    template <Arithmetic T, std::size_t N, typename Tag, TupleConvertable<Tag> Tag_>
    constexpr Tuple<T, N, Tag> operator+(const Tuple<T, N, Tag>& a, const Tuple<T, N, Tag_>& b)
    {
        auto res{a};
        res += b;
        return res;
    }

    template <Arithmetic T, std::size_t N, typename Tag, TupleConvertable<Tag> Tag_>
    constexpr Tuple<T, N, Tag> operator-(const Tuple<T, N, Tag>& a, const Tuple<T, N, Tag_>& b)
    {
        auto res{a};
        res -= b;
        return res;
    }

    template <Arithmetic T, std::size_t N, typename Tag, std::convertible_to<T> T_>
    constexpr Tuple<T, N, Tag> operator*(const Tuple<T, N, Tag>& a, T_ s)
    {
        auto res{a};
        res *= s;
        return res;
    }

    template <Arithmetic T, std::size_t N, typename Tag, std::convertible_to<T> T_>
    constexpr Tuple<T, N, Tag> operator*(T_ s, const Tuple<T, N, Tag>& x)
    {
        return x * s;
    }

    template <Arithmetic T, std::size_t N, typename Tag, std::convertible_to<T> T_>
    constexpr Tuple<T, N, Tag> operator/(const Tuple<T, N, Tag>& a, T_ s)
    {
        auto res{a};
        res /= s;
        return res;
    }

    template <SignedArithmetic T, std::size_t N, typename Tag>
    constexpr Tuple<T, N, Tag> operator-(const Tuple<T, N, Tag>& x)
    {
        auto res{x};
        res *= -1;
        return res;
    }

    template <Arithmetic T, std::size_t N, typename Tag, TupleConvertable<Tag> Tag_>
    constexpr bool operator==(const Tuple<T, N, Tag>& a, const Tuple<T, N, Tag_>& b)
    {
        for (std::size_t i{0}; i != N; i++) {
            if (a[i] != b[i]) {
                return false;
            }
        }
        return true;
    }

    template <Arithmetic T, std::size_t N, typename Tag, TupleConvertable<Tag> Tag_>
    constexpr bool operator!=(const Tuple<T, N, Tag>& a, const Tuple<T, N, Tag_>& b)
    {
        return !(a == b);
    }

    template <std::size_t... Indecies, Arithmetic T, std::size_t N, typename Tag>
        requires(details::indecies_valid<N, Indecies...>)
    constexpr auto swizzle(const Tuple<T, N, Tag>& t)
    {
        return Tuple<T, sizeof...(Indecies), Tag>{t[Indecies]...};
    }

} // namespace Raychel

template <Raychel::Arithmetic T, std::size_t N, typename Tag>
struct std::tuple_size<Raychel::Tuple<T, N, Tag>>
{
    static constexpr auto value = N;
};

template <std::size_t I, Raychel::Arithmetic T, std::size_t N, typename Tag>
    requires(I < N)
struct std::tuple_element<I, Raychel::Tuple<T, N, Tag>>
{
    using type = T;
};

#endif //!RAYCHELMATH_TUPLE_H
