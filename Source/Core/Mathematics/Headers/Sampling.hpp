//
// Created by Vojtěch Pröschl on 16.09.2022.
//

#ifndef NPRG045_SAMPLING_HPP
#define NPRG045_SAMPLING_HPP

#include "Coordinates.hpp"

#include <UT/UT_Vector2.h>
#include <UT/UT_Vector3.h>



//Default generator is uniform
class Generator{
public:
    virtual float Generate01F1();
    virtual UT_Vector2F Generate01F2();
    virtual UT_Vector3F Generate01F3();
};

class SampleGenerator{
public:
    float Uniform01();
    UT_Vector2F Uniform01V2();
    UT_Vector3F Uniform01V3();
    PolarCoordinates UniformDisk();
    UT_Vector3F CosineWeightedHemisphereSample();
    UT_Vector3F PhongSample();
    UT_Vector3F GXXSample()
};

#endif //NPRG045_SAMPLING_HPP
