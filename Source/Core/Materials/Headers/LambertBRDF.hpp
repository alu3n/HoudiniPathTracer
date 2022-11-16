//
// Created by Vojtěch Pröschl on 16.09.2022.
//

#ifndef NPRG045_LAMBERTBRDF_HPP
#define NPRG045_LAMBERTBRDF_HPP

#include "BxDF.hpp"

class LambertBRDF : public BRDF{
public:
    LambertBRDF(Color albedo);
    virtual Color Evaluate(UT_Vector3F V, UT_Vector3F L);
    virtual UT_Vector3F Sample(UT_Vector3F V);
    virtual float PDF(UT_Vector3F V, UT_Vector3F sample);
private:
    Color albedo;
};

#endif //NPRG045_LAMBERTBRDF_HPP
