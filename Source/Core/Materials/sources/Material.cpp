//
// Created by Vojtěch Pröschl on 09.12.2022.
//

#include "../include/Material.hpp"

TextureData ConstantMaterial::Evaluate(UT_Vector3F position) {
    return data;
}

ConstantMaterial::ConstantMaterial(TextureData data) : data(data) {}