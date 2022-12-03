//
// Created by Vojtěch Pröschl on 14.11.2022.
//

#ifndef NPRG045_BXDF_HPP
#define NPRG045_BXDF_HPP

#include <array>
//#include "../../Mathematics/include/Vectors.hpp"
#include "../../Mathematics/include/Sampling.hpp"
#include "../../Physics/include/Radiometry.hpp"
#include "Texture.hpp"

class BRDF{
public:
    void Load(Texture * texture, UT_Vector3F position);
    virtual std::array<float,3> Evaluate(UT_Vector3F incomming, UT_Vector3F outgoing, UT_Vector3F normal) = 0;
    virtual UT_Vector3F GenerateSample(UT_Vector3F incomming, UT_Vector3F normal) = 0;
    TextureData data{{0,0,0},0,0,0};
};

class BTDF{
public:
    void Load(Texture * texture, UT_Vector3F position);
    virtual std::array<float,3> Evaluate(UT_Vector3F incomming, UT_Vector3F outgoing, UT_Vector3F normal) = 0;
    virtual UT_Vector3F GenerateSample(UT_Vector3F incomming, UT_Vector3F normal) = 0;
    TextureData data{{0,0,0},0,0,0};
};

class BSDF{
public:
    void Load(Texture * texture, UT_Vector3F position);
    BRDF * brdf;
    BTDF * btdf;
};

#endif //NPRG045_BXDF_HPP
