//
// Created by Vojtěch Pröschl on 16.09.2022.
//

#ifndef NPRG045_PROCEDURAL_HPP
#define NPRG045_PROCEDURAL_HPP

#include <UT/UT_Vector3.h>
#include "../../Physics/Headers/Radiometry.hpp"

struct TextureData{
    RGBRadiance Color;
    float Roughness;
    float Transparency;
    float IOR;
};

class Texture{
public:
    virtual TextureData Evaluate(UT_Vector3F position) = 0;
};

class ConstantTexture : public Texture{
public:
    virtual TextureData Evaluate(UT_Vector3F position) override;
    ConstantTexture(TextureData data);
private:
    TextureData data;
};

#endif //NPRG045_PROCEDURAL_HPP
