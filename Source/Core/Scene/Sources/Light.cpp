//
// Created by Vojtěch Pröschl on 17.09.2022.
//


#include "../Headers/Light.hpp"
#include "UT/UT_Matrix3.h"

Light::Light(UT_Vector3F position) {
    Position = position;
}

ConstantPointLight::ConstantPointLight(UT_Vector3F position, fpreal intensity) : Light(position){
    Intensity = intensity;
}

LightSample ConstantPointLight::GenerateSample() {
    return {Position,Intensity};
}

ConstantRectangularAreaLight::ConstantRectangularAreaLight(UT_Vector3F position, UT_Vector3F orientation,
                                                           UT_Vector2F size, fpreal intensity) : Light(position) {
    dirX = UT_Vector3F(size.x(),0,0);
    dirY = UT_Vector3F(0,size.y(),0);

    UT_Matrix3F T(1.0);
    T.rotate<0>(orientation.x(),orientation.y(),orientation.z());

    dirX = dirX*T;
    dirY = dirY*T;

    Position = position - 0.5*dirX - 0.5*dirY;

    this->intensity = intensity;
}

LightSample ConstantRectangularAreaLight::GenerateSample() {
    auto sample = generator.Generate01F2();
    auto pos = Position + sample.x()*dirX + sample.y()*dirY;
    return {pos,intensity};
}