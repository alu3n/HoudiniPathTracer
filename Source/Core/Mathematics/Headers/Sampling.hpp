//
// Created by Vojtěch Pröschl on 16.09.2022.
//

#ifndef NPRG045_SAMPLING_HPP
#define NPRG045_SAMPLING_HPP

#include <UT/UT_Vector2.h>
#include <UT/UT_Vector3.h>

//Default generator is uniform
class Generator{
public:
    virtual float Generate01F1();
    virtual UT_Vector2F Generate01F2();
    virtual UT_Vector3F Generate01F3();
};

#endif //NPRG045_SAMPLING_HPP
