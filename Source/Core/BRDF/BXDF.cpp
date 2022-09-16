//
// Created by Vojtěch Pröschl on 16.09.2022.
//

#include "BXDF.hpp"

void BRDF::LoadData(UT_Vector3F L, UT_Vector3F V, UT_Vector3F N, UT_Vector3F H, UT_Vector3F R, UT_Vector3F T, UT_Vector3F P) {
    this->L = L;
    this->V = V;
    this->N = N;
    this->H = H;
    this->R = R;
    this->T = T;
    this->P = P;
}