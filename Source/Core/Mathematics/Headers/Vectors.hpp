//
// Created by Vojtěch Pröschl on 17.09.2022.
//

#ifndef NPRG045_VECTORS_HPP
#define NPRG045_VECTORS_HPP

#include <UT/UT_Vector3.h>

template<int p>
float Norm(UT_Vector3F V){
    return pow(pow(V.x(),p)+pow(V.y(),p)+pow(V.z(),p),1.0/p);
}

template<int p>
UT_Vector3F Normalize(UT_Vector3F V){
    return (1.0/Norm<p>(V))*V;
}


#endif //NPRG045_VECTORS_HPP
