//
// Created by Vojtěch Pröschl on 18.11.2022.
//

#ifndef NPRG045_PHYSICALLYBASEDBXDF_HPP
#define NPRG045_PHYSICALLYBASEDBXDF_HPP

#include "BxDF.hpp"

class PB_BRDF : public BRDF{
    std::array<float,3> Evaluate(UT_Vector3F incomming, UT_Vector3F outgoing,  UT_Vector3F normal) override;
    UT_Vector3F GenerateSample(UT_Vector3F incomming, UT_Vector3F normal) override;
};

class PB_BTDF : public BTDF{
    std::array<float,3> Evaluate(UT_Vector3F incomming, UT_Vector3F outgoing,  UT_Vector3F normal) override;
    UT_Vector3F GenerateSample(UT_Vector3F incomming, UT_Vector3F normal) override;
};

class PB_BSDF : public BSDF{
public:
    PB_BSDF();
};

float D_GGX(UT_Vector3F normal, UT_Vector3F halfway,float roughness);
float G_GGX(UT_Vector3F normal, UT_Vector3F halfway, UT_Vector3F);
float D_PHONG(UT_Vector3F normal, UT_Vector3F halfway,float phongExp);
float G_CookTorrance(UT_Vector3F light, UT_Vector3F view, UT_Vector3F halfway, UT_Vector normal);
float F_Schlick(); // fresnell schlicks approximation
//float Fresnell()


#endif //NPRG045_PHYSICALLYBASEDBXDF_HPP
