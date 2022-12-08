//
// Created by Vojtěch Pröschl on 14.11.2022.
//

#ifndef NPRG045_QUANTITIES_HPP
#define NPRG045_QUANTITIES_HPP

#include <stdexcept>
#include <array>


struct RGBEnergy{
    float R;
    float G;
    float B;
};


RGBEnergy operator+(const RGBEnergy &, const RGBEnergy &);
RGBEnergy operator-(const RGBEnergy &, const RGBEnergy &);
RGBEnergy operator*(const RGBEnergy &, const RGBEnergy &);
RGBEnergy operator/(const RGBEnergy &, const RGBEnergy &);

RGBEnergy operator*(float, const RGBEnergy &);
RGBEnergy operator/(float, const RGBEnergy &);

#endif //NPRG045_QUANTITIES_HPP
