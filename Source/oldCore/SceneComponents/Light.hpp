//
// Created by Vojtěch Pröschl on 08.09.2022.
//

#ifndef NPRG045_LIGHT_HPP
#define NPRG045_LIGHT_HPP

#include <UT/UT_Vector3.h>
#include "../Utility//SampleGenerators.hpp"

struct LightSample{
    UT_Vector3F myPosition;
    fpreal myIntensity;
};

class Light{
public:
    Light(UT_Vector3F position);
    virtual LightSample GenerateSample() = 0;
protected:
    fpreal Intensity;
    UT_Vector3F Position;
};

class ConstantPointLight : public Light{
public:
    ConstantPointLight(UT_Vector3F position, fpreal intensity);
    LightSample GenerateSample() override;
private:
    fpreal Intensity;
};

class ConstantRectangularAreaLight : public Light{
public:
    ConstantRectangularAreaLight(UT_Vector3F position, UT_Vector3F orientation, UT_Vector2F size, fpreal intensity);
    LightSample GenerateSample() override;
private:
    UT_Vector3F dirX;
    UT_Vector3F dirY;
    UniformGenerator generator;
    fpreal intensity;
};

#endif //NPRG045_LIGHT_HPP
