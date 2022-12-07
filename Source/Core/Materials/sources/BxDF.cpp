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
//constexpr int phongEXP = 1000;

UT_Vector3F PerfectReflection(UT_Vector3F incomming, UT_Vector3F normal){
    return incomming - (dot(normal,incomming)*normal)*2;
}

std::array<float, 3>
BSDF::EvaluateBRDF(const TextureData & textureData, UT_Vector3F outgoingDir, UT_Vector3F incommingDir, UT_Vector3F normalDir) {
    auto normal = normalDir;

    auto fresnell = ReflectionCoefficient(incommingDir,normal,incIOR,outIOR); //reflected:refracted
    auto refractedCoeff = 1/(fresnell+1);
    auto reflectedCoeff = 1-refractedCoeff;
    auto perfectDir = PerfectReflection(incommingDir,normal);

    auto temp0 = dot(incommingDir,normal);

    auto diffuse = temp0 > 0 ? dot(incommingDir,normal) * (1-textureData.Transparency) : 0;

    auto temp = dot(perfectDir,outgoingDir);

    auto phongEXP = textureData.ReflectionRoughness > 0.001 ? 1/textureData.ReflectionRoughness : 1/0.001;

    auto specular = temp > 0 ? pow(dot(perfectDir,outgoingDir),phongEXP) : 0;
    auto C = textureData.DiffuseColor;

    float R = C[0]*diffuse*refractedCoeff+reflectedCoeff*specular;
    float G = C[1]*diffuse*refractedCoeff+reflectedCoeff*specular;
    float B = C[2]*diffuse*refractedCoeff+reflectedCoeff*specular;

    if(R < 0 || G < 0 || B < 0){
        std::cout << R << " : " << G << " : " << B << std::endl;
    }

    return {R,G,B};
}

UT_Vector3F BSDF::GenerateReflection(const TextureData & textureData, UT_Vector3F incommingDir, UT_Vector3F normalDir) {
    auto normal = normalDir;

    auto normalInSpherical = CartesianToSpherical(normal);
    auto azimuth = Generator::GenerateF01()*2*M_PI;
    auto zenith = Generator::GenerateF01()*M_PI-0.5*M_PI;
    auto nextPath = SphericalCoords(azimuth,zenith);
    nextPath.zenith += normalInSpherical.zenith;
    nextPath.azimuth += normalInSpherical.azimuth;
    auto randomPath = SphericalToCartesian(nextPath);
    auto temp = textureData.ReflectionRoughness * randomPath + (1-textureData.ReflectionRoughness) * PerfectReflection(incommingDir,normal);
    return Normalize(temp);
}

//constexpr float ratioIOR = 0.75;

std::array<float, 3> BSDF::EvaluateBSDF(const TextureData & textureData) {
    return {1,1,1};
}


UT_Vector3F BSDF::GenerateRefraction(const TextureData & textureData, UT_Vector3F incommingDir, UT_Vector3F normalDir, float IOR1, float IOR2) {
    auto normal = normalDir;

    auto normalInSpherical = CartesianToSpherical(normal);
    auto azimuth = Generator::GenerateF01()*2*M_PI;
    auto zenith = Generator::GenerateF01()*M_PI-0.5*M_PI;
    auto nextPath = SphericalCoords(azimuth,zenith);
    nextPath.zenith += normalInSpherical.zenith;
    nextPath.azimuth += normalInSpherical.azimuth;
    auto randomPath = SphericalToCartesian(nextPath);


    auto l = incommingDir;
    auto n = normalDir;

    auto n12 = IOR1/IOR2;
    float dt = dot(l,n);

    auto c1 = 1 - dt*dt;
    c1 = n12*n12*c1;
    c1 = 1 - c1;
    c1 = sqrt(c1);
    c1 = n12*dt-c1;
    auto A = c1*n;
    auto B = n12*l;
    auto perfect = A - B;

    return Normalize(perfect*(1-textureData.RefractionRoughness) + randomPath*textureData.RefractionRoughness);
}