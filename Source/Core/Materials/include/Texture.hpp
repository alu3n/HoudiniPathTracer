//
// Created by Vojtěch Pröschl on 16.09.2022.
//

#ifndef NPRG045_PROCEDURAL_HPP
#define NPRG045_PROCEDURAL_HPP


#include <array>
#include <UT/UT_Vector3.h>

#include "../../Physics/include/Units.hpp"

struct TextureData{
    RGBEnergy DiffuseColor;
    float ReflectionRoughness;
    float RefractionRoughness;
    float Transparency;
    float IOR;
};

#endif //NPRG045_PROCEDURAL_HPP
