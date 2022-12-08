//
// Created by Vojtěch Pröschl on 17.09.2022.
//

#include "../include/Sampling.hpp"

float Generator::GenerateF01() {
    return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}

int Generator::GenerateIRange(int min, int max) {
    auto rand = Generator::GenerateF01();
    rand*=(max-min+1);
    if(rand > max) return max;
    if(rand < min) return min;
    return ((int)rand)+min;
}

float Generator::GenerateFRange(float min, float max) {
    auto dist = max - min;
    return min + GenerateF01()*dist;
}

UT_Vector3F Generator::RandomDir(UT_Vector3F normalDir) {
    auto normalInSpherical = CartesianToSpherical(normalDir);
    auto azimuth = Generator::GenerateF01()*2*M_PI;
    auto zenith = Generator::GenerateF01()*M_PI-0.5*M_PI;
    auto nextPath = SphericalCoords(azimuth,zenith);
    nextPath.zenith += normalInSpherical.zenith;
    nextPath.azimuth += normalInSpherical.azimuth;
    auto randomDir = SphericalToCartesian(nextPath);
    return randomDir;
}
