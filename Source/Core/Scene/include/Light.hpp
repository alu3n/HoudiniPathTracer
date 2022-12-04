//
// Created by Vojtěch Pröschl on 15.11.2022.
//

#ifndef NPRG045_LIGHT_HPP
#define NPRG045_LIGHT_HPP

#include "../../Mathematics/include/Sampling.hpp"
#include "../../Physics/include/Radiometry.hpp"

using Radiance = RadiometricQuantity<RadiometricQuantities::Radiance>;

struct LightSample{
    UT_Vector3F lightPos;
    UT_Vector3F lightDir;
    float lightDistance;
    float intensity;
};

class Light{
public:
    virtual LightSample GenerateSample(UT_Vector3F targetPosition) = 0;
};

class ConstantRectangularLight : public Light {
public:
    ConstantRectangularLight(UT_Vector3F position, UT_Vector3F orientation, UT_Vector2F size, float constantIntensity);
    LightSample GenerateSample(UT_Vector3F targetPosition) override;
private:
    float ConstantIntensity;
    UT_Vector3F dirX;
    UT_Vector3F dirY;
    Generator generator{};
    UT_Vector3F position;
};

#endif //NPRG045_LIGHT_HPP
