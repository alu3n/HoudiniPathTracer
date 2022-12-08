//
// Created by Vojtěch Pröschl on 15.11.2022.
//

#ifndef NPRG045_LIGHT_HPP
#define NPRG045_LIGHT_HPP

#include "../../Mathematics/include/Sampling.hpp"
#include "../../Physics/include/Units.hpp"

//using Radiance = RadiometricQuantity<RadiometricQuantities::Radiance>;

struct LightSample{
    UT_Vector3F LightPos;
    UT_Vector3F LightDir;
    float LightDistance;
    RGBEnergy Energy;
};

class Light{
public:
    virtual LightSample GenerateSample(UT_Vector3F targetPosition) = 0;
};

class ConstantRectangularLight : public Light {
public:
    ConstantRectangularLight(UT_Vector3F position, UT_Vector3F orientation, UT_Vector2F size, float constantIntensity, RGBEnergy);
    LightSample GenerateSample(UT_Vector3F targetPosition) override;
private:
    float ConstantIntensity;
    RGBEnergy Color;
    UT_Vector3F dirX;
    UT_Vector3F dirY;
    UT_Vector3F position;
};

#endif //NPRG045_LIGHT_HPP
