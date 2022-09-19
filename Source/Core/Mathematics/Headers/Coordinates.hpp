//
// Created by Vojtěch Pröschl on 19.09.2022.
//

#ifndef NPRG045_COORDINATES_HPP
#define NPRG045_COORDINATES_HPP

#include <UT/UT_Vector.h>

struct PolarCoordinates{
    float r = 0;
    float azimuth = 0;
    PolarCoordinates(float r, float azimuth);
    PolarCoordinates(float azimuth);
    PolarCoordinates() = default;
};

struct SphericalCoords{
    float r = 0;
    float azimuth = 0;
    float zenith = 0;
    SphericalCoords(float r, float azimuth, float zenith);
    SphericalCoords(float azimuth, float zenith);
    SphericalCoords() = default;
};

PolarCoordinates CartesianToPolar(UT_Vector2F coords);
SphericalCoords CartesianToSpherical(UT_Vector3F coords);

UT_Vector2F PolarToCartesian(PolarCoordinates coords);
UT_Vector3F SphericalToCartesian(SphericalCoords coords);


#endif //NPRG045_COORDINATES_HPP
