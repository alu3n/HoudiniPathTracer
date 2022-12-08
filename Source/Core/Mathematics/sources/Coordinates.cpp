//
// Created by Vojtěch Pröschl on 19.09.2022.
//

#include "../include/Coordinates.hpp"
#include "../include/LinearAlgebra.hpp"

SphericalCoords::SphericalCoords(float r, float azimuth, float zenith) {
    this->r = r;
    this->azimuth = azimuth;
    this->zenith = zenith;
}

SphericalCoords::SphericalCoords(float azimuth, float zenith) {
    this->azimuth = azimuth;
    this->zenith = zenith;
    this->r = 1;
}

SphericalCoords CartesianToSpherical(UT_Vector3F coords){
    float cy = coords.y() == 0 ? 0.00001 : coords.y();

    return {
        Norm(coords),
        atan(coords.x()/cy)
    };
}

UT_Vector3F SphericalToCartesian(SphericalCoords coords){
    return {
        coords.r * cos(coords.azimuth) * sin(coords.zenith),
        coords.r * sin(coords.azimuth) * sin(coords.zenith),
        coords.r * cos(coords.zenith)
    };
}
