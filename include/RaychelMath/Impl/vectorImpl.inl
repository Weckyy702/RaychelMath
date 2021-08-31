/**
* \file vectorImpl.inl
* \author Weckyy702 (weckyy702@gmail.com)
* \brief Implementation for the functions in vector.h
* \date 2021-07-08
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
#ifndef RAYCHEL_VECTOR_IMPL_H
#define RAYCHEL_VECTOR_IMPL_H

#include <cmath>
#include "../constants.h"
#include "../vector.h"

namespace Raychel {

    template <std::floating_point T>
    vec3Imp<T> rotateX(const vec3Imp<T>& v, T theta) noexcept
    {
        using std::sin, std::cos;
        return {v.x, v.y * cos(theta) - v.z * sin(theta), v.y * sin(theta) + v.z * cos(theta)};
    }

    template <std::floating_point T>
    vec3Imp<T> rotateY(const vec3Imp<T>& v, T theta) noexcept
    {
        using std::sin, std::cos;
        return {v.x * cos(theta) + v.z * sin(theta), v.y, -v.x * sin(theta) + v.z * cos(theta)};
    }

    template <std::floating_point T>
    vec3Imp<T> rotateZ(const vec3Imp<T>& v, T theta) noexcept
    {
        using std::sin, std::cos;
        return {v.x * cos(theta) - v.y * sin(theta), v.x * sin(theta) + v.y * cos(theta), v.z};
    }

    template <std::floating_point T>
    constexpr vec3Imp<T> reflect(const vec3Imp<T>& direction, const vec3Imp<T>& normal) noexcept
    {
        RAYCHEL_ASSERT_NORMALIZED(direction);
        return direction - (normal * T(dot(direction, normal) * 2.0));
    }

    template <std::floating_point T>
    vec3Imp<T> get_tangent(const vec3Imp<T>& normal) noexcept
    {
        auto tangent = vec3Imp<T>{normal.z, normal.z, -normal.x - normal.y};
        if (magSq(tangent) == 0) {
            tangent = vec3Imp<T>{-normal.y - normal.z, normal.x, normal.x};
        }
        return normalize(tangent);
    }

    template <std::floating_point T>
    std::tuple<vec3Imp<T>, vec3Imp<T>, vec3Imp<T>> get_basis_vectors(const vec3Imp<T>& normal) noexcept
    {
        const auto j = normalize(normal);
        const auto k = get_tangent(j);
        const auto i = cross(j, k);
        return {i, j, k};
    }

    template <std::floating_point T, typename RNG_t, typename>
    vec3Imp<T> get_random_direction_on_hemisphere(const vec3Imp<T>& normal, const RNG_t& rng) noexcept
    {
        auto test = normalize(vec3Imp<T>{rng(), rng(), rng()});
        if (dot(test, normal) < 0) {
            test *= -1;
        }
        return test;
    }

    template <std::floating_point T, std::invocable<T> RNG_t>
    vec3Imp<T> get_random_direction_on_cone_angle(const vec3Imp<T>& normal, T half_cone_angle, const RNG_t& rng) noexcept
    {
        using std::sin, std::cos;
        if (half_cone_angle != 0) {
            half_cone_angle = std::clamp<T>(half_cone_angle, 0, half_pi<T>);
            const auto theta = rng() * half_cone_angle;
            const auto phi = rng() * pi_v<T>;

            const auto [i, j, k] = get_basis_vectors(normal);

            return normalize((i * sin(theta) * sin(phi)) + (j * cos(theta)) + (k * cos(phi) * sin(theta)));
        }
        return normal;
    }

} // namespace Raychel

#endif //!RAYCHEL_VECTOR_IMPL_H