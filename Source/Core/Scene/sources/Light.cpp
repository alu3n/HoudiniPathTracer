//
// Created by Vojtěch Pröschl on 17.09.2022.
//


//#include "../include/OldLight.hpp"
#include "../include/Light.hpp"
#include "../../Mathematics/include/LinearAlgebra.hpp"
#include "UT/UT_Matrix3.h"

ConstantRectangularLight::ConstantRectangularLight(UT_Vector3F position, UT_Vector3F orientation, UT_Vector2F size, float constantIntensity, RGBRadiance color) : color(color){
    dirX = UT_Vector3F(size.x(),0,0);
    dirY = UT_Vector3F(0,size.y(),0);

    UT_Matrix3F T(1.0);
    T.rotate<0>(orientation.x(),orientation.y(),orientation.z());

    dirX = dirX*T;
    dirY = dirY*T;

    this->position = position - 0.5*dirX - 0.5*dirY;
    ConstantIntensity = constantIntensity;
}

LightSample ConstantRectangularLight::GenerateSample(UT_Vector3F targetPosition) {
    auto sample = Generator::GenerateF01<2>();
    auto onLightPosition = position + sample[0]*dirX + sample[1]*dirY;
    auto directionTargetToLight = onLightPosition - targetPosition;
    return {onLightPosition,Normalize(directionTargetToLight),Norm(directionTargetToLight),ConstantIntensity,color};
}