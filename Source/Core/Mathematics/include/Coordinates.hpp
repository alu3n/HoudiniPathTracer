//
// Created by Vojtěch Pröschl on 19.09.2022.
//

#ifndef NPRG045_COORDINATES_HPP
#define NPRG045_COORDINATES_HPP

#include <UT/UT_Vector.h>

/*
 * This file is intended to store definitions of all classes and functions regarding Coordinates
 */

struct SphericalCoords{
    float r = 0;
    float azimuth = 0;
    float zenith = 0;
    SphericalCoords(float r, float azimuth, float zenith);
    SphericalCoords(float azimuth, float zenith);
    SphericalCoords() = default;
};

SphericalCoords CartesianToSpherical(UT_Vector3F coords);

UT_Vector3F SphericalToCartesian(SphericalCoords coords);


#endif //NPRG045_COORDINATES_HPP
