//
// Created by Vojtěch Pröschl on 17.09.2022.
//

#ifndef NPRG045_VECTORS_HPP
#define NPRG045_VECTORS_HPP

#include <UT/UT_Vector.h>

/*
 * This header is intended to store declarations of classes and functions related to linear algebra,
 * that don't fit other header file better.
 */

UT_Vector3F Normalize(UT_Vector3F v);
float Norm(UT_Vector3F v);

#endif //NPRG045_VECTORS_HPP
