/*DONT FORGET THE COPYRIGHT ;)*/
#ifndef RAYCHEL_MATH_FORWARD_H
#define RAYCHEL_MATH_FORWARD_H

#include <cstddef>
#include <gsl/gsl>
#include "RaychelCore/compat.h"
#include "concepts.h"

namespace Raychel {
    using gsl::not_null; //NOLINT(misc-unused-using-decls)
    using std::size_t;   //NOLINT(misc-unused-using-decls)

    template <Arithmetic _number>
    struct vec2Imp;

    template <Arithmetic _number>
    struct vec3Imp;

    template <Arithmetic _number>
    struct colorImp;

    /*
    template<Arithmetic T>
    struct colorAImp;
    */

    template <std::floating_point _real>
    struct QuaternionImp;

    template <std::floating_point _real>
    struct Transform;
} // namespace Raychel

#endif //!RAYCHEL_MATH_FORWARD_H