/*DONT FORGET THE COPYRIGHT ;)*/
#ifndef RAYCHEL_MATH_FORWARD_H
#define RAYCHEL_MATH_FORWARD_H

#include <cstddef>
#include "RaychelCore/compat.h"
#include "concepts.h"

namespace Raychel {

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
    struct TransformImp;
} // namespace Raychel

#endif //!RAYCHEL_MATH_FORWARD_H