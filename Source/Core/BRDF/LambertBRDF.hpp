//
// Created by Vojtěch Pröschl on 16.09.2022.
//

#ifndef NPRG045_LAMBERT_HPP
#define NPRG045_LAMBERT_HPP

#include "BXDF.hpp"

class LambertBRDF : public BRDF{
public:
    float Evaluate() override;
    Sample RaySample() override;
    Sample EvaluateIndirect() override;
    float PDF() override;
private:

};

#endif //NPRG045_LAMBERT_HPP
