/**
* \file vector.h
* \author Weckyy702 (weckyy702@gmail.com)
* \brief Additional vector functions for RaychelMath
* \date 2021-07-07
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
#ifndef RAYCHEL_VECTOR_H
#define RAYCHEL_VECTOR_H

#include <array>
#include "constants.h"
#include "vec3.h"

namespace Raychel {

    /**
	*\brief Rotate the vector theta radians around positive X
	*
	*\tparam T Type of the vector
	*\param v Vector to rotate
	*\param theta Angle to rotate by. Must be in radians
	*\return basic_vec3<T>
	*/
    template <Arithmetic T>
    constexpr basic_vec3<T> rotate_x(const basic_vec3<T>& v, T theta) noexcept
    {
        using std::sin, std::cos;
        return basic_vec3<T>{v[0], v[1] * cos(theta) - v[2] * sin(theta), v[1] * sin(theta) + v[2] * cos(theta)};
    }

    /**
	*\brief Rotate the vector theta radians around positive Y
	*
	*\tparam T Type of the vector
	*\param v Vector to rotate
	*\param theta Angle to rotate by. Must be in radians
	*\return basic_vec3<T>
	*/
    template <std::floating_point T>
    constexpr basic_vec3<T> rotate_y(const basic_vec3<T>& v, T theta) noexcept
    {
        using std::sin, std::cos;
        return basic_vec3<T>{v[0] * cos(theta) + v[2] * sin(theta), v[1], -v[0] * sin(theta) + v[2] * cos(theta)};
    }

    /**
	*\brief Rotate the vector theta radians around positive Z
	*
	*\tparam T Type of the vector
	*\param v Vector to rotate
	*\param theta Angle to rotate by. Must be in radians
	*\return basic_vec3<T>
	*/
    template <std::floating_point T>
    constexpr basic_vec3<T> rotate_z(const basic_vec3<T>& v, T theta) noexcept
    {
        using std::sin, std::cos;
        return basic_vec3<T>{v[0] * cos(theta) - v[1] * sin(theta), v[0] * sin(theta) + v[1] * cos(theta), v[2]};
    }
    /**
	*\brief Reflect vector along normal
	*
	*\tparam T Type of the vector
	*\param dir direction to be reflected
	*\param normal normal to reflect around
	*\return basic_vec3 the reflected vector
	*/
    template <std::floating_point T>
    constexpr basic_vec3<T> reflect(const basic_vec3<T>& direction, const basic_vec3<T>& normal) noexcept
    {
        RAYCHEL_ASSERT_NORMALIZED(direction);
        return direction - (normal * T(dot(direction, normal) * 2.0));
    }

    /**
    * \brief Get the tangent to normal
    *
    * \tparam T type of vector
    * \param normal normal to find the tangent to
    * \return
    */
    template <std::floating_point T>
    basic_vec3<T> get_tangent(const basic_vec3<T>& normal) noexcept
    {
        auto tangent = basic_vec3<T>{normal[2], normal[2], -normal[0] - normal[1]};
        if (mag_sq(tangent) == 0) {
            tangent = basic_vec3<T>{-normal[1] - normal[2], normal[0], normal[0]};
        }
        return normalize(tangent);
    }

    /**
    * \brief Get the basis vectors around normal
    *
    * \tparam T type of vector
    * \param normal +Y axis for the local coordinate frame
    * \return +x, +y, +z axis as a tuple
    */
    template <std::floating_point T>
    std::array<basic_vec3<T>, 3> get_basis_vectors(const basic_vec3<T>& normal) noexcept
    {
        const auto j = normalize(normal);
        const auto k = get_tangent(j);
        const auto i = cross(j, k);
        return {i, j, k};
    }

    /**
    * \brief Get a random direction on the hemisphere around normal
    *
    * \tparam T type of vector
    * \tparam RNG_t type of RNG used to generate the random distribution
    * \param normal normal vector for the hemisphere
    * \param rng random number generator used to generate the distribution
    * \return
    */
    template <std::floating_point T, std::invocable RNG_t>
    basic_vec3<T> get_random_direction_on_hemisphere(const basic_vec3<T>& normal, const RNG_t& rng) noexcept
    {
        auto test = normalize(basic_vec3<T>{rng(), rng(), rng()});
        if (dot(test, normal) < 0) {
            test *= -1;
        }
        return test;
    }

    /**
    * \brief Get a random direction on a cone angle
    *
    * \tparam T type of vector
    * \tparam RNG_t type of RNG used to generate the random distribution
    * \param normal normal of the cone
    * \param cone_angle angle between the normal and the cones sides
    * \param rng random number generator used to generate the distribution
    * \return
    */
    template <std::floating_point T, std::invocable RNG_t>
    basic_vec3<T> get_random_direction_on_cone_angle(const basic_vec3<T>& normal, T half_cone_angle, const RNG_t& rng) noexcept
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

#endif //!RAYCHEL_VECTOR_H
