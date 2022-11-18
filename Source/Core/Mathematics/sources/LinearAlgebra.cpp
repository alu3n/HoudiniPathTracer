//
// Created by Vojtěch Pröschl on 18.11.2022.
//

#include <exception>
#include "../include/LinearAlgebra.hpp"

float Norm(UT_Vector3F v){
    return sqrt(v.x()*v.x() + v.y()*v.y() + v.z()*v.z());
}

UT_Vector3F Normalize(UT_Vector3F v){
    auto size = Norm(v);
    if(size == 0) throw std::invalid_argument( "norm must be non-zero" );
    return (1/size) * v;
}