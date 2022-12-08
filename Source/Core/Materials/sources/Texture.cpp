//
// Created by Vojtěch Pröschl on 16.11.2022.
//

#include "../include/Texture.hpp"

TextureData ConstantMaterial::Evaluate(UT_Vector3F position) {
    return data;
}

ConstantMaterial::ConstantMaterial(TextureData data) : data(data) {}