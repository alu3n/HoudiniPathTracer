//
// Created by Vojtěch Pröschl on 16.09.2022.
//

#ifndef NPRG045_UNITS_HPP
#define NPRG045_UNITS_HPP

#include <array>

enum class PhysicalQuantity{
    Radiosity, //Will be used for light sources
    Radiance
};

template<PhysicalQuantity>
struct Quantity{
    float amount;
};

template<PhysicalQuantity Q>
struct Color{
    Quantity<Q> R;
    Quantity<Q> G;
    Quantity<Q> B;
    float alpha;
};

#endif //NPRG045_UNITS_HPP
