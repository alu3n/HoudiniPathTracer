//
// Created by Vojtěch Pröschl on 18.11.2022.
//

#ifndef NPRG045_PHYSICALLYBASEDBXDF_HPP
#define NPRG045_PHYSICALLYBASEDBXDF_HPP

#include "BxDF.hpp"

class PB_BRDF : public BRDF{
    std::array<float,3> Evaluate(UT_Vector3F incomming, UT_Vector3F outgoing) override;
    UT_Vector3F GenerateSample(UT_Vector3F incomming, UT_Vector3F normal) override;
};

class PB_BTDF : public BTDF{
    std::array<float,3> Evaluate(UT_Vector3F incomming, UT_Vector3F outgoing) override;
    UT_Vector3F GenerateSample(UT_Vector3F incomming, UT_Vector3F normal) override;
};

class PB_BSDF : public BSDF{
public:
    PB_BSDF();
};


#endif //NPRG045_PHYSICALLYBASEDBXDF_HPP
