//
// Created by Vojtěch Pröschl on 17.09.2022.
//

#include "../include/Optics.hpp"

float ReflectionCoefficient(UT_Vector3F vectorToSource, UT_Vector3F normal, float travelingFromIOR, float travelingToIOR){
    auto R0 = pow(((travelingFromIOR-travelingToIOR)/(travelingFromIOR+travelingToIOR)),2);
    return R0 + (1-R0)*pow(1-dot(vectorToSource,normal),5);
}