//
// Created by Vojtěch Pröschl on 16.11.2022.
//

#include "../Headers/Texture.hpp"

TextureData ConstantTexture::Evaluate(UT_Vector3F position) {
    return data;
}

ConstantTexture::ConstantTexture(TextureData data) : data(data) {}