//
// Created by Vojtěch Pröschl on 16.09.2022.
//

#ifndef NPRG045_PHYSICS_HPP
#define NPRG045_PHYSICS_HPP

#include <array>

enum class PhysicalQuantity{
    Radiosity, //Will be used for light sources
    Radiance
};

template<PhysicalQuantity>
struct Unit{
    float amount;
};

template<PhysicalQuantity Quantity,int SampleCount>
struct Spectrum{
    std::array<Unit<Quantity>,SampleCount> data;
};

#endif //NPRG045_PHYSICS_HPP
