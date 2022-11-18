//
// Created by Vojtěch Pröschl on 16.09.2022.
//

#ifndef NPRG045_OLDLIGHT_HPP
#define NPRG045_OLDLIGHT_HPP

#include "../../Mathematics/include/Sampling.hpp"

struct OldLightSample{
    UT_Vector3F myPosition;
    fpreal myIntensity;
};

class OldLight{
public:
    OldLight(UT_Vector3F position);
    virtual OldLightSample GenerateSample() = 0;
protected:
    fpreal Intensity;
    UT_Vector3F Position;
};

class ConstantPointLight : public OldLight{
public:
    ConstantPointLight(UT_Vector3F position, fpreal intensity);
    OldLightSample GenerateSample() override;
private:
    fpreal Intensity;
};

class ConstantRectangularAreaLight : public OldLight{
public:
    ConstantRectangularAreaLight(UT_Vector3F position, UT_Vector3F orientation, UT_Vector2F size, fpreal intensity);
    OldLightSample GenerateSample() override;
private:
    UT_Vector3F dirX;
    UT_Vector3F dirY;
    Generator generator{};
    fpreal intensity;
};

#endif //NPRG045_OLDLIGHT_HPP
