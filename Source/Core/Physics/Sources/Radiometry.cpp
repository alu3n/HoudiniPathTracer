//
// Created by Vojtěch Pröschl on 16.11.2022.
//

#include "../Headers/Radiometry.hpp"

RGBRadiance operator+(const RGBRadiance & C1, const RGBRadiance & C2){
    return {C1[0] + C2[0],C1[1] + C2[1],C1[2] + C2[2]};
}
RGBRadiance operator-(const RGBRadiance & C1, const RGBRadiance & C2){
    return {C1[0] - C2[0],C1[1] - C2[1],C1[2] - C2[2]};
}
RGBRadiance operator*(float a, const RGBRadiance &C){
    return {C[0]*a,C[1]*a,C[2]*a};
}