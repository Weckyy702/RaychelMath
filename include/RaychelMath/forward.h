/**
* \file forward.h
* \author Weckyy702 (weckyy702@gmail.com)
* \brief Header file for forward class
* \date 2022-03-27
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
#ifndef RAYCHELMATH_FORWARD_H
#define RAYCHELMATH_FORWARD_H

#include "RaychelCore/compat.h"
#include "concepts.h"

namespace Raychel {

    template <Arithmetic T, std::size_t N, typename Tag>
    requires(N != 0) class Tuple;

    struct vec2Tag;
    struct vec3Tag;
    struct colorTag;
    struct QuaternionTag;

    template <Arithmetic T>
    struct transform;
} // namespace Raychel

#endif //!RAYCHELMATH_FORWARD_H
