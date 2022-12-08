//
// Created by Vojtěch Pröschl on 16.11.2022.
//

#include "../include/Units.hpp"

RGBEnergy operator+(const RGBEnergy & A, const RGBEnergy & B){
    return {A.R + B.R, A.G + B.G, A.B + B.B};
}

RGBEnergy operator-(const RGBEnergy & A, const RGBEnergy & B){
    return {A.R - B.R, A.G - B.G, A.B - B.B};
}

RGBEnergy operator*(const RGBEnergy & A, const RGBEnergy & B){
    return {A.R * B.R, A.G * B.G, A.B * B.B};
}

RGBEnergy operator/(const RGBEnergy & A, const RGBEnergy & B){
    return {A.R / B.R, A.G / B.G, A.B / B.B};
}

RGBEnergy operator*(float a, const RGBEnergy & B){
    return {a*B.R,a*B.G,a*B.B};
}

RGBEnergy operator/(const RGBEnergy & A,float b){
    return {A.R/b,A.G/b,A.B/b};
}
