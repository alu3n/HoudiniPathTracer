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

//RGBRadiance operator*(float a, const RGBRadiance & B){
//    return {a*B[0].amount,a*B[1].amount,a*B[2].amount};
//}

constexpr float incIOR = 1;
constexpr float outIOR = 1.5;
constexpr int phongEXP = 10;

UT_Vector3F PerfectReflection(UT_Vector3F incomming, UT_Vector3F normal){
    return incomming - (dot(normal,incomming)*normal)*2;
}

std::array<float, 3>
BSDF::EvaluateBRDF(const TextureData & textureData, UT_Vector3F outgoingDir, UT_Vector3F incommingDir, UT_Vector3F normalDir) {
    auto fresnell = ReflectionCoefficient(incommingDir,normalDir,incIOR,outIOR); //reflected:refracted
    auto refractedCoeff = 1/(fresnell+1);
    auto reflectedCoeff = 1-refractedCoeff;
    auto perfectDir = PerfectReflection(incommingDir,normalDir);

    auto diffuse = dot(incommingDir,normalDir);
    auto specular = pow(dot(perfectDir,outgoingDir),phongEXP);
    auto C = textureData.DiffuseColor;

    float R = C[0]*diffuse*refractedCoeff+reflectedCoeff*specular;
    float G = C[1]*diffuse*refractedCoeff+reflectedCoeff*specular;
    float B = C[2]*diffuse*refractedCoeff+reflectedCoeff*specular;

    return {R,G,B};
}

UT_Vector3F BSDF::GenerateReflection(const TextureData & textureData, UT_Vector3F incommingDir, UT_Vector3F normalDir) {
    auto normalInSpherical = CartesianToSpherical(normalDir);
    auto azimuth = Generator::GenerateF01()*2*M_PI;
    auto zenith = Generator::GenerateF01()*M_PI-0.5*M_PI;
    auto nextPath = SphericalCoords(azimuth,zenith);
    nextPath.zenith += normalInSpherical.zenith;
    nextPath.azimuth += normalInSpherical.azimuth;
    auto randomPath = SphericalToCartesian(nextPath);
    auto temp = textureData.ReflectionRoughness * randomPath + (1-textureData.ReflectionRoughness) * PerfectReflection(incommingDir,normalDir);
    if(Norm(temp) == 0){
        std::cout << "ACHTUNG BxDF" << std::endl;
    }

    return Normalize(temp);
//    return{0,1,0};
}