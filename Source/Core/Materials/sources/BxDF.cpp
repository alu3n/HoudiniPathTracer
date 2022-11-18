//
// Created by Vojtěch Pröschl on 16.11.2022.
//

#include "../include/BxDF.hpp"

void BRDF::Load(Texture *texture, UT_Vector3F position) {
    this->data = texture->Evaluate(position);
}

void BTDF::Load(Texture *texture, UT_Vector3F position) {
    this->data = texture->Evaluate(position);
}

void BSDF::Load(Texture *texture, UT_Vector3F position) {
    brdf->Load(texture,position);
    btdf->Load(texture,position);
}