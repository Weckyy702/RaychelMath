/*DONT FORGET THE COPYRIGHT ;)*/
#ifndef RAYCHEL_MATH_FORWARD_H
#define RAYCHEL_MATH_FORWARD_H

#include <cstddef>
#include "RaychelCore/compat.h"
#include "concepts.h"

namespace Raychel {

    template <Arithmetic T, std::size_t N, typename Tag>
    requires(N != 0) class Tuple;

    struct vec2Tag;
    struct vec3Tag;
    struct colorTag;
    struct quaternionTag;

    template <std::floating_point _real>
    struct transform;
} // namespace Raychel

#endif //!RAYCHEL_MATH_FORWARD_H