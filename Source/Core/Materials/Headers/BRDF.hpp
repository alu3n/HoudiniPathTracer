//
// Created by Vojtěch Pröschl on 14.11.2022.
//

#ifndef NPRG045_BRDF_HPP
#define NPRG045_BRDF_HPP

#include <array>
#include "../../Mathematics/Headers/Vectors.hpp"
#include "../../Mathematics/Headers/Sampling.hpp"
#include "../../Physics/Headers/Radiometry.hpp"
#include "Texture.hpp"

class BRDF{
public:
    virtual void Load(Texture * texture, UT_Vector3F position);
    virtual std::array<float,3> Evaluate(UT_Vector3F incomming, UT_Vector3F outgoing) = 0;
    virtual UT_Vector3F GenerateSample(UT_Vector3F incomming, UT_Vector3F normal) = 0;
protected:
    TextureData data{{0,0,0},0,0,0};
};

class PBBRDF : public BRDF{
public:
    virtual std::array<float,3> Evaluate(UT_Vector3F incomming, UT_Vector3F outgoing) override;
    virtual UT_Vector3F GenerateSample(UT_Vector3F incomming, UT_Vector3F normal) override;
private:
    Generator gen;
};

#endif //NPRG045_BRDF_HPP
