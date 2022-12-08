//
// Created by Vojtěch Pröschl on 16.11.2022.
//

#include "../../Physics/include/Optics.hpp"
#include "../include/BxDF.hpp"
#include "../../Mathematics/include/LinearAlgebra.hpp"

std::array<float,3> operator*(const std::array<float,3> & A,const std::array<float,3> & B){
    return {A[0]*B[0],A[1]*B[1],A[2]*B[2]};
}

RGBRadiance operator*(const std::array<float,3> & A, const RGBRadiance & B){
    return {A[0]*B[0].amount,A[1]*B[1].amount,A[2]*B[2].amount};
}

std::array<float, 3> BSDF::EvaluateDiffuseBRDF(const TextureData & textureData, UT_Vector3F outgoingDir, UT_Vector3F observationDir,
                                               UT_Vector3F normalDir) {
    auto multiplier = dot(observationDir,normalDir);
    multiplier = multiplier > 0 ? multiplier * (1-textureData.Transparency) : 0;
    return {multiplier*textureData.DiffuseColor[0],multiplier*textureData.DiffuseColor[1],multiplier*textureData.DiffuseColor[2]};
}

std::array<float, 3> BSDF::EvaluateSpecularBRDF(const TextureData & textureData, UT_Vector3F outgoingDir, UT_Vector3F incommingDir,
                                                UT_Vector3F normalDir) {
    auto perfectDir = PerfectReflection(incommingDir,normalDir);
    auto temp = dot(perfectDir,outgoingDir);
    auto phongEXP = textureData.ReflectionRoughness > 0.001 ? 1/textureData.ReflectionRoughness : 1/0.001;
    float specular = temp > 0 ? pow(dot(perfectDir,outgoingDir),phongEXP) : 0;
    return {specular,specular,specular};
}

std::array<float, 3>
BSDF::EvaluateBRDF(const TextureData & textureData, UT_Vector3F outgoingDir, UT_Vector3F incommingDir, UT_Vector3F normalDir) {
    auto fresnell = SchlickApproximation(incommingDir, normalDir, 1, textureData.IOR); //reflected:refracted
    auto refractedCoeff = 1/(fresnell+1);
    auto reflectedCoeff = 1-refractedCoeff;

    auto diffuse = EvaluateDiffuseBRDF(textureData,outgoingDir,incommingDir,normalDir);
    auto specular = EvaluateSpecularBRDF(textureData,outgoingDir,incommingDir,normalDir);

    float R = diffuse[0]*refractedCoeff+reflectedCoeff*specular[0];
    float G = diffuse[1]*refractedCoeff+reflectedCoeff*specular[1];
    float B = diffuse[2]*refractedCoeff+reflectedCoeff*specular[2];

    return {R,G,B};
}

UT_Vector3F BSDF::GenerateReflection(const TextureData & textureData, UT_Vector3F observationDir, UT_Vector3F normalDir) {
    auto randomDir = Generator::RandomDir(normalDir);
    auto perfectDir = PerfectReflection(observationDir,normalDir);

    auto reflectionDir = textureData.ReflectionRoughness * randomDir + (1-textureData.ReflectionRoughness) * perfectDir;
    return Normalize(reflectionDir);
}


std::array<float, 3> BSDF::EvaluateBTDF(const TextureData & textureData) {
    return {1,1,1};
    //Todo: Implement this function :)
}


UT_Vector3F BSDF::GenerateRefraction(const TextureData & textureData, UT_Vector3F observationDir, UT_Vector3F normalDir, float IOR1, float IOR2) {
    auto randomDir = Generator::RandomDir(normalDir);
    auto perfectDir = PerfectRefraction(observationDir,normalDir,IOR1,IOR2);

    auto refractionDir = Normalize(perfectDir*(1-textureData.RefractionRoughness) + randomDir*textureData.RefractionRoughness);
    return refractionDir;
}