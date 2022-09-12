//
// Created by Vojtěch Pröschl on 10.09.2022.
//

#include "Math.hpp"

fpreal myNorm(UT_Vector3F vec){
    return sqrt(
            vec.x()*vec.x()+
            vec.y()*vec.y()+
            vec.z()*vec.z()
    );
}

UT_Vector3F myNormalize(UT_Vector3F vec){
    return (1.0/myNorm(vec))*vec;
}

fpreal myMax(fpreal A, fpreal B){
    if(A > B) return A;
    return B;
}