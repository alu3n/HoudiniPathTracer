//
// Created by Vojtěch Pröschl on 05.09.2022.
//

#ifndef NPRG045_SAMPLEGENERATOR_HPP
#define NPRG045_SAMPLEGENERATOR_HPP

#include <UT/UT_Vector2.h>
#include <UT/UT_Vector3.h>

class SampleGenerator{
public:
    virtual fpreal Generate01D1();
    virtual UT_Vector2F Generate01D2();
    virtual UT_Vector3F Generate01D3();
    //Todo: Create multiple sample generators which will be passed to camera etc. in constructor to get different results
};

class UniformGenerator : public SampleGenerator {
public:
    explicit UniformGenerator(float seed);
    fpreal Generate01D1() override;
    UT_Vector2F Generate01D2() override;
    UT_Vector3F Generate01D3() override;
};



#endif //NPRG045_SAMPLEGENERATOR_HPP
