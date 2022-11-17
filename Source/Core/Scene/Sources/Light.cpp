//
// Created by Vojtěch Pröschl on 17.09.2022.
//


//#include "../include/OldLight.hpp"
#include "../Headers/Light.hpp"
#include "UT/UT_Matrix3.h"

ConstantRectangularLight::ConstantRectangularLight(UT_Vector3F position, UT_Vector3F orientation, UT_Vector2F size,
                                                   Radiance radiance) : constantRadiance(radiance){
    dirX = UT_Vector3F(size.x(),0,0);
    dirY = UT_Vector3F(0,size.y(),0);

    UT_Matrix3F T(1.0);
    T.rotate<0>(orientation.x(),orientation.y(),orientation.z());

    dirX = dirX*T;
    dirY = dirY*T;

    this->position = position - 0.5*dirX - 0.5*dirY;
}

LightSample ConstantRectangularLight::GenerateSample(UT_Vector3F targetPosition) {
    auto sample = generator.Generate01F2();
    auto onLightPosition = position + sample.x()*dirX + sample.y()*dirY;
    auto directionTargetToLight = onLightPosition - targetPosition;
    return {onLightPosition,directionTargetToLight,constantRadiance};
}