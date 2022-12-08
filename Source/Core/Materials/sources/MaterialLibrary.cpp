//
// Created by Vojtěch Pröschl on 07.12.2022.
//

#include "../include/MaterialLibrary.hpp"
#include "../../Mathematics/include/LinearAlgebra.hpp"

MaterialMarble::MaterialMarble() : ConstantMaterial({}){
    data.RefractionRoughness = 0.26;
    data.ReflectionRoughness = 0.26;
    data.Transparency = 0;
    data.IOR = 1.486;
    data.DiffuseColor = {0.59,0.61,0.65};
}

MaterialRubber::MaterialRubber() : ConstantMaterial({}){
    data.RefractionRoughness = 0.6;
    data.ReflectionRoughness = 0.6;
    data.Transparency = 0;
    data.IOR = 1.5;
    data.DiffuseColor = {0.018,0.018,0.018};
}

MaterialPorcelain::MaterialPorcelain() : ConstantMaterial({}){
    data.RefractionRoughness = 0;
    data.ReflectionRoughness = 0;
    data.Transparency = 0;
    data.IOR = 1.5;
    data.DiffuseColor = {0.9,0.9,0.9};
}

MaterialGlass::MaterialGlass() : ConstantMaterial({}) {
    data.RefractionRoughness = 0;
    data.ReflectionRoughness = 0;
    data.Transparency = 1;
    data.IOR = 3;
    data.DiffuseColor = {0.2,0.2,0.2};
}

MaterialDefault::MaterialDefault() : ConstantMaterial({}) {
    data.RefractionRoughness = 0.21;
    data.ReflectionRoughness = 0.21;
    data.Transparency = 0;
    data.IOR = 1.486;
    data.DiffuseColor = {255.0/152,255.0/155,255.0/167};
}
//Rename to piano lacquer
MaterialPianoBlack::MaterialPianoBlack() : ConstantMaterial({}) {
    data.RefractionRoughness = 0.01;
    data.ReflectionRoughness = 0.01;
    data.Transparency = 0;
    data.IOR = 1.5;
    data.DiffuseColor = {0.002,0.002,0.002};
}

MaterialRock::MaterialRock() : ConstantMaterial({}) {
    data.RefractionRoughness = 1;
    data.ReflectionRoughness = 1;
    data.Transparency = 0;
    data.IOR = 1.5;
    data.DiffuseColor = {0.7,0.7,0.7};
}

MaterialPlastic::MaterialPlastic() : ConstantMaterial({}){
    data.RefractionRoughness = 0.3;
    data.ReflectionRoughness = 0.3;
    data.Transparency = 0;
    data.IOR = 1.5;
    data.DiffuseColor = {0.755,0.560625,0.141185};
}

constexpr float period = 1;

TextureData ProceduralTiles::Evaluate(UT_Vector3F position) {
    float mult = M_PI*2*period;
    float val = sin(position.x()*mult+0.9912938)*sin(position.y()*mult)*sin(position.z()*mult+1.378271);

    std::array<float,3> Cd{0,0,0};

    if(val > 0){
        Cd = {1,1,1};
    }
    else{

    }

    return {Cd,0.3,0.3,0,1.5};
}















