//
// Created by Vojtěch Pröschl on 17.09.2022.
//

#include "../include/Optics.hpp"

float ReflectionCoefficient(UT_Vector3F incomming, UT_Vector3F normal, float IOR1, float IOR2){
    auto R0 = pow(((IOR1-IOR2)/(IOR1+IOR2)),2);
//    std::cout << R0 << std::endl;
    return R0 + (1-R0)*pow(1-dot(incomming,normal),5);
}