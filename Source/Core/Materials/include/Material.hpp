//
// Created by Vojtěch Pröschl on 09.12.2022.
//

#ifndef NPRG045_MATERIAL_HPP
#define NPRG045_MATERIAL_HPP

#include "Texture.hpp"

/*
 * Materials are used to drive the appearance, the BSDF utilizes TextureData values
 * for its computations, material is responsible for generating of TextureData values
 * at a certain point.
 *
 * Materials can be used to create both procedural R3->TextureSpace which vary depending
 * on the position in 3D space and textures that are constant.
 *
 * For procedural textures use Material as predecessor, for constant use ConstantMaterial
 */

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
