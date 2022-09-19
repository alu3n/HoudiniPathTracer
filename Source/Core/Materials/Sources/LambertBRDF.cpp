//
// Created by Vojtěch Pröschl on 17.09.2022.
//

#include "../Headers/LambertBRDF.hpp"

float LambertBRDF::PDF(UT_Vector3F V, UT_Vector3F sample) {

}

RaySample LambertBRDF::Sample(UT_Vector3F V) {
    
}

Color LambertBRDF::Evaluate(UT_Vector3F V, UT_Vector3F L) {
    Color temp;

    temp.R = albedo.R;
    temp.G = albedo.G;
    temp.B = albedo.B;
    temp.alpha = 0;

    return temp;
}

LambertBRDF::LambertBRDF(Color albedo) {
    this->albedo = albedo;
}