//
// Created by Vojtěch Pröschl on 16.09.2022.
//

#ifndef NPRG045_UNITS_HPP
#define NPRG045_UNITS_HPP

#include <array>

/* TODO:
 * - [ ] Implement addition, multiplication etc.
 */

enum class PhysicalQuantity{
    Radiosity, //Will be used for light sources
    Radiance,
    Energy
};

template<PhysicalQuantity>
struct Quantity{
    float amount = 0;
};

//struct Color{
//    Quantity<PhysicalQuantity::Energy> R;
//    Quantity<PhysicalQuantity::Energy> G;
//    Quantity<PhysicalQuantity::Energy> B;
//    float alpha = 0;
//};

//Color operator+(const Color & C1, const Color & C2);
//Color operator*(float a,const Color & C);

#endif //NPRG045_UNITS_HPP
