//
// Created by Vojtěch Pröschl on 16.11.2022.
//

#include "../Headers/BRDF.hpp"

void BRDF::Load(Texture *texture, UT_Vector3F position) {
    this->data = texture->Evaluate(position);
}

std::array<float, 3> PBBRDF::Evaluate(UT_Vector3F incomming, UT_Vector3F outgoing) {
    return {0,0,0};
}

//Note: Inccomming... pointing from observer to the intersection
UT_Vector3F PBBRDF::GenerateSample(UT_Vector3F incomming, UT_Vector3F normal) {
    auto normalInSpherical = CartesianToSpherical(normal);
    auto azimuth = gen.Generate01F1()*2*M_PI;
    auto zenith = gen.Generate01F1()*M_PI-0.5*M_PI;
    auto nextPath = SphericalCoords(azimuth,zenith);
    nextPath.zenith += normalInSpherical.zenith;
    nextPath.azimuth += normalInSpherical.azimuth;
    auto randomPath = SphericalToCartesian(nextPath);
    auto perfectPath = incomming - (dot(normal,incomming)*normal)*2;

    return data.Roughness * randomPath + (1-data.Roughness) * perfectPath;
}