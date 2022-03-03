/**
* \file concepts.h
* \author Weckyy702 (weckyy702@gmail.com)
* \brief Math-related concepts
* \date 2021-08-30
* 
* MIT License
* Copyright (c) [2021] [Weckyy702 (weckyy702@gmail.com | https://github.com/Weckyy702)]
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
#ifndef RAYCHEL_MATH_CONCEPTS_H
#define RAYCHEL_MATH_CONCEPTS_H

#include <concepts>
#include <type_traits>
#include <random>

namespace Raychel {

    namespace details {

        template<typename T>
        concept Void = std::is_void_v<T>;

        template<typename P, typename D>
        concept StdRandomNumberDistributionParamType = requires(P p)
        {
            std::is_copy_constructible_v<P>;
            std::is_copy_assignable_v<P>;
            std::equality_comparable<P>;

            typename P::distribution_type;
            std::same_as<typename P::distribution_type, D>;
        };

    } // namespace details

    template <typename T>
    concept Arithmetic = requires(const T a)
    {
        {a + a} -> std::convertible_to<T>;
        {a - a} -> std::convertible_to<T>;
        {a * a} -> std::convertible_to<T>;
        {a / a} -> std::convertible_to<T>;
    };

    template<typename T>
    concept SignedArithmetic = Arithmetic<T> && std::is_signed_v<T>;

    template<typename E>
    concept StdRandomNumberEngine = requires(E e, const E x, unsigned long long z, std::ostream& os, std::istream& is)
    {
        std::uniform_random_bit_generator<E>;

        typename E::result_type;

        E();
        std::is_constructible_v<E, typename E::result_type>;
        E(x);
        E(e);
        //E(q) with q satisfying SeedSequence

        { e.seed() } -> details::Void;
        { e.seed(std::declval<typename E::result_type>())} -> details::Void;
        //e.seed(q) with q satisfying SeedSequence

        { e() } -> std::same_as<typename E::result_type>;

        { e.discard(z) } -> details::Void;

        { x == e } -> std::same_as<bool>;
        { x != e } -> std::same_as<bool>;

        { os << x } -> std::same_as<decltype(os)&>;
        { is >> e } -> std::same_as<decltype(is)&>;
    };

    template<typename D>
    concept StdRandomNumberDistribution = requires(D d, const D x, std::ostream& os, std::istream& is)
    {
        std::is_copy_constructible_v<D>;
        std::is_copy_assignable_v<D>;

        typename D::result_type;
        typename D::param_type;

        details::StdRandomNumberDistributionParamType<typename D::param_type, D>;

        D();
        std::is_constructible_v<D, typename D::param_type>;

        { d.reset() } -> details::Void;
        { x.param() } -> std::same_as<typename D::param_type>;
        { d.param(std::declval<typename D::param_type>()) } -> details::Void;

        //d(g) with g satisfying std::uniform_random_bit_generator
        //d(g, p) with g satisfying std::uniform_random_bit_generator and p being a value of type D::param_type;

        { x.min() } -> std::same_as<typename D::result_type>;
        { x.max() } -> std::same_as<typename D::result_type>;

        { x == d } -> std::same_as<bool>;
        { x != d } -> std::same_as<bool>;

        { os << x } -> std::same_as<decltype(os)&>;
        { is >> d } -> std::same_as<decltype(is)&>;
    };
} // namespace Raychel

#endif //!RAYCHEL_MATH_CONCEPTS_H