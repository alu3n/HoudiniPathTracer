//
// Created by Vojtěch Pröschl on 18.11.2022.
//

#include "../include/PB_BxDF.hpp"

UT_Vector3F PerfectReflection(UT_Vector3F incomming, UT_Vector3F normal){
    return incomming - (dot(normal,incomming)*normal)*2;
}

//float phongExp = 20;

std::array<float, 3> PB_BRDF::Evaluate(UT_Vector3F incomming, UT_Vector3F outgoing, UT_Vector3F normal) {
    auto perfectPath = PerfectReflection(incomming,normal);

    float phongExp = data.Roughness < 0.001 ? 1000 : 1/data.Roughness;

    float multiplier = pow(dot(outgoing,perfectPath),phongExp)*data.Metalic + (1-data.Metalic);
    return {multiplier,multiplier,multiplier};
}

UT_Vector3F PB_BRDF::GenerateSample(UT_Vector3F incomming, UT_Vector3F normal) {
    auto normalInSpherical = CartesianToSpherical(normal);
    auto azimuth = Generator::GenerateF01()*2*M_PI;
    auto zenith = Generator::GenerateF01()*M_PI-0.5*M_PI;
    auto nextPath = SphericalCoords(azimuth,zenith);
    nextPath.zenith += normalInSpherical.zenith;
    nextPath.azimuth += normalInSpherical.azimuth;
    auto randomPath = SphericalToCartesian(nextPath);

    return data.Roughness * randomPath + (1-data.Roughness) * PerfectReflection(incomming,normal);
}

std::array<float, 3> PB_BTDF::Evaluate(UT_Vector3F incomming, UT_Vector3F outgoing, UT_Vector3F normal) {


    return {1,1,1};
}

UT_Vector3F PB_BTDF::GenerateSample(UT_Vector3F incomming, UT_Vector3F normal) {
    return {0,1,0};
}

PB_BSDF::PB_BSDF() {
    this->brdf = new PB_BRDF();
    this->btdf = new PB_BTDF();
}