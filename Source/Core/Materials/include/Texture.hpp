//
// Created by Vojtěch Pröschl on 16.09.2022.
//

#ifndef NPRG045_PROCEDURAL_HPP
#define NPRG045_PROCEDURAL_HPP


#include <array>
#include <UT/UT_Vector3.h>

#include "../../Physics/include/Units.hpp"

struct TextureData{
//    std::array<float,3> DiffuseColor;
    RGBEnergy DiffuseColor;
    float ReflectionRoughness;
    float RefractionRoughness;
    float Transparency;
    float IOR;
};

class Material{
public:
    virtual TextureData Evaluate(UT_Vector3F position) = 0;
};

class ConstantMaterial : public Material{
public:
    virtual TextureData Evaluate(UT_Vector3F position) override;
    ConstantMaterial(TextureData data);
protected:
    TextureData data;
};

#endif //NPRG045_PROCEDURAL_HPP
