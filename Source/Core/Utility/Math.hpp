//
// Created by Vojtěch Pröschl on 10.09.2022.
//

#ifndef NPRG045_MATH_HPP
#define NPRG045_MATH_HPP

#include <UT/UT_Vector3.h>
#include <UT/UT_Vector4.h>

fpreal myNorm(UT_Vector3F vec);

UT_Vector3F myNormalize(UT_Vector3F vec);

fpreal myMax(fpreal A, fpreal B);

#endif //NPRG045_MATH_HPP
