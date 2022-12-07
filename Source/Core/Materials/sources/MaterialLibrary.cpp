//
// Created by Vojtěch Pröschl on 07.12.2022.
//

#include "../include/MaterialLibrary.hpp"

MaterialMarble::MaterialMarble() : ConstantTexture({}){
    data.RefractionRoughness = 0.26;
    data.ReflectionRoughness = 0.26;
    data.Transparency = 0;
    data.IOR = 1.486;
    data.DiffuseColor = {0.59,0.61,0.65};
}

MaterialRubber::MaterialRubber() : ConstantTexture({}){
    data.RefractionRoughness = 0.6;
    data.ReflectionRoughness = 0.6;
    data.Transparency = 0;
    data.IOR = 1.5;
    data.DiffuseColor = {0.018,0.018,0.018};
}

MaterialPorcelain::MaterialPorcelain() : ConstantTexture({}){
    data.RefractionRoughness = 0;
    data.ReflectionRoughness = 0;
    data.Transparency = 0;
    data.IOR = 1.5;
    data.DiffuseColor = {0.9,0.9,0.9};
}

MaterialGlass::MaterialGlass() : ConstantTexture({}) {
    data.RefractionRoughness = 0;
    data.ReflectionRoughness = 0;
    data.Transparency = 1;
    data.IOR = 1.5;
    data.DiffuseColor = {0.2,0.2,0.2};
}

MaterialDefault::MaterialDefault() : ConstantTexture({}) {
    data.RefractionRoughness = 0.21;
    data.ReflectionRoughness = 0.21;
    data.Transparency = 0;
    data.IOR = 1.486;
    data.DiffuseColor = {255.0/152,255.0/155,255.0/167};
}
//Rename to piano lacquer
MaterialPianoBlack::MaterialPianoBlack() : ConstantTexture({}) {
    data.RefractionRoughness = 0.01;
    data.ReflectionRoughness = 0.01;
    data.Transparency = 0;
    data.IOR = 1.5;
    data.DiffuseColor = {0.002,0.002,0.002};
}

MaterialRock::MaterialRock() : ConstantTexture({}) {
    data.RefractionRoughness = 1;
    data.ReflectionRoughness = 1;
    data.Transparency = 0;
    data.IOR = 1.5;
    data.DiffuseColor = {0.7,0.7,0.7};
}

MaterialPlastic::MaterialPlastic() : ConstantTexture({}){
    data.RefractionRoughness = 0.3;
    data.ReflectionRoughness = 0.3;
    data.Transparency = 0;
    data.IOR = 1.5;
    data.DiffuseColor = {0.755,0.560625,0.141185};
}