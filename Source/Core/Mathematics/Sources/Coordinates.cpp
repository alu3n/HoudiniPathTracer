//
// Created by Vojtěch Pröschl on 19.09.2022.
//

#include "../Headers/Coordinates.hpp"
#include "../Headers/Vectors.hpp"

PolarCoordinates::PolarCoordinates(float r, float azimuth) {
    this->r = r;
    this->azimuth = azimuth;
}

PolarCoordinates::PolarCoordinates(float azimuth) {
    this->r = 1;
    this->azimuth = azimuth;
}

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

PolarCoordinates CartesianToPolar(UT_Vector2F coords){

}

SphericalCoords CartesianToSpherical(UT_Vector3F coords){
    return {
        Norm<2>(coords),
        atan(coords.x()/coords.y())
    };
}

UT_Vector2F PolarToCartesian(PolarCoordinates coords){

}

UT_Vector3F SphericalToCartesian(SphericalCoords coords){
    return {
        coords.r * cos(coords.azimuth) * sin(coords.zenith),
        coords.r * sin(coords.azimuth) * sin(coords.zenith),
        coords.r * cos(coords.zenith)
    };
}
