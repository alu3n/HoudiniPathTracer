//
// Created by Vojtěch Pröschl on 09.12.2022.
//

#ifndef NPRG045_MATERIAL_HPP
#define NPRG045_MATERIAL_HPP

#include "Texture.hpp"

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

#endif //NPRG045_MATERIAL_HPP
