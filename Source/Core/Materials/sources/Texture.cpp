//
// Created by Vojtěch Pröschl on 16.11.2022.
//

#include "../include/Texture.hpp"

TextureData ConstantTexture::Evaluate(UT_Vector3F position) {
    return data;
}

ConstantTexture::ConstantTexture(TextureData data) : data(data) {

}

TextureData ProceduralTexture::Evaluate(UT_Vector3F position) {
    auto data = TextureData{{1,1,1},1.5,0.5,0};
    return data;
//    data.DiffuseColor = {abs(sin(position.x()*10)),abs(sin(position.y()*10)),abs(sin(position.z()*10))};
}